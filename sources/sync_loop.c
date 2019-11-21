
#include "../includes/file_sync.h"
#include <errno.h>
#include <poll.h>

struct pollfd fds[4];
int pollfd_list = 0;


void       push_pollfd_array(int sockfd) {

    if (pollfd_list == 4) {
        return ;
    }
    struct pollfd fdlist_object;

    fdlist_object.fd = sockfd;
    fdlist_object.events = POLLIN;
    //if (pollfd_list == 0)

    fdlist_object.revents = 0;
    /*else fdlist_object.revents = POLLOUT; */
    fds[pollfd_list] = fdlist_object;
    pollfd_list++;
}


typedef struct socket_list {
    int sockfd;
    char *ip;
    bool sync_or_not;
    struct socket_list *next;
}   socket_t;

socket_t *new_socket(int sockfd, char *ip) {
    socket_t *new_sock;

    new_sock = (socket_t *)malloc(sizeof(socket_t));
    new_sock->ip = strdup(ip);
    new_sock->sockfd = sockfd;
    new_sock->next = NULL;
    return (new_sock);
}

socket_t *add_socket(socket_t *head, int sockfd, char *ip) {
    socket_t *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = (socket_t *)malloc(sizeof(socket_t));
    trav->next->ip = strdup(ip);
    trav->next->sockfd = sockfd;
    trav->next->next = NULL;
    return (trav);
}


socket_t *push_socket(socket_t *head, int sockfd, char *ip) {
    socket_t *trav;

    trav = head;
    if (trav == NULL)
        head = new_socket(sockfd, ip);
    else {
        trav = add_socket(head, sockfd, ip);
        trav = head;
    }
    return (head);
}

void print_linked_list(socket_t *head) {
    socket_t *current;

    current = head;
    while (current) {
        printf("%d  -> ", current->sockfd);
        current = current->next;
    }
}

size_t LOCAL_PORT_ASSIGNMENT(void)
{
    char buffer[6];
    struct stat info;
    size_t size;

    int fd = open("test_client.txt", O_RDONLY);
    fstat(fd, &info);
    bzero(buffer, 6);
    read(fd, buffer, info.st_size);
    size = atoi(buffer);
    close(fd);
    return (size);
}

void  reset_pollfds_list(socket_t *socket_list) {
    socket_t *current_socket;

    current_socket = socket_list;
    while (current_socket) {
        push_pollfd_array(current_socket->sockfd);
        current_socket = current_socket->next;
    }
}


int accept_new_connection(int sockfd, struct sockaddr_in socket_address) {
    int accept_socket;
    socklen_t address_len;
    char buffer[4096];

    address_len = sizeof(socket_address);
    accept_socket = accept(sockfd, (struct sockaddr *)&socket_address, &address_len);

    if (accept_socket) {
        printf("new connectin\n");
        return (accept_socket);
    }
    return (-1);
}



void   broadcast_message(int transmitter, int this_socket, socket_t *sockets,
        unsigned char *remote_filesys) {
    socket_t *current;

    current = sockets;
    while (current) {
        if (current->sockfd == this_socket || current->sockfd == transmitter) {
            current = current->next;
            continue ;
        }
        broadcast_send(current->sockfd, remote_filesys);
        current = current->next;
    }
}

int  checking_polling_list(int sockfd, int this_socket, socket_t *sockets) {
    int index;
    char buffer[4096];
    int flag = -1;
    socket_t *current_list;

     
    bzero(buffer, 4096);
    index = 0;
    index = 0;
    while (index < pollfd_list) {
        
        if (fds[index].fd == this_socket) {
            
            index++;
            continue ;
        } 
        if (fds[index].revents) {
            
            printf("checking_polling_list ()\n");

            unsigned char *remote_filesys = NULL;

            remote_filesys = broadcast_recv(fds[index].fd);
             
            flag = fds[index].fd;
            
            broadcast_message(fds[index].fd, this_socket, sockets, remote_filesys);
        } 
        index++; 
        
    }
    return (flag);
}


void            broadcast_new_node(unsigned char *remote_filesys, socket_t *socket_list,
        int new_socket, int this_server_sock) {

    socket_t    *current_socket;

    current_socket = socket_list;
    while (current_socket) {
        if (current_socket->sockfd == new_socket || current_socket->sockfd == this_server_sock) {
           current_socket = current_socket->next;
           continue;
        }
        printf("broadcast_new_node()\n");
        //handshake(current_socket->sockfd, SERVER);
        broadcast_send(current_socket->sockfd, remote_filesys);
        printf("after broadcast_send\n");
        //write(current_socket->sockfd, remote_filesys, 4000);
        current_socket = current_socket->next;
    }
}



int        handle_client_side(socket_t *socket_list, int extra_socket) {

    int counter = 0;
    int flag = -1;

    printf("Preemptive strike\n");

    while (counter < pollfd_list) {
        if (fds[counter].fd == extra_socket) {
            if (fds[counter].revents & POLLIN) {
                flag = 1;
                printf("handle_client_side()\n");
                //handshake(fds[counter].fd, CLIENT);
                unsigned char *remote_filesys = broadcast_recv(fds[counter].fd);
                break;
            }
        }
        counter++;
    }
    return (flag);
}

static int DEBUG_SOCKET(void) {
    int fd = open("test_client.txt", O_RDONLY);
    char buffer[4096];
    bzero(buffer, 4096);

    read(fd, buffer, 4096);
    printf("PORT NUMBER : %s\n", buffer);
    close(fd);
    return (atoi(buffer));
}


struct sockaddr_in  create_client_side_server(int *sockfd) {
    struct sockaddr_in socket_address;

    *sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if (*sockfd < 0)
        perror("socket");
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(DEBUG_SOCKET());

    if (bind(*sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0) 
        perror("binding");

    if (listen(*sockfd, 5)) 
        perror("listen");

    return (socket_address);
}


socket_t        *assign_client_socket(int *client_side, socket_t *socket_list)
{
    struct sockaddr_in client_address;
    char *client_ip;

    create_client_side_server(client_side);
    client_ip = inet_ntoa(client_address.sin_addr);
    socket_list = push_socket(socket_list, *client_side, client_ip);
    return (socket_list);
}

void            sync_loop(int sockfd, int client_type, 
            struct sockaddr_in socket_address,
            int extra_sock, char *extra_ip, int user_or_api)
{
    int32_t         max_file_descriptor;
    int32_t         trigger;
    socket_t        *socket_list;
    int             newsock;
   
    int             death = extra_sock;
    int             client_side;
    char            *ip;
    unsigned char   *remote_filesys;

    socket_list = NULL;
    if (client_type == CLIENT)
        socket_list = assign_client_socket(&client_side, socket_list);
    
    ip = inet_ntoa(socket_address.sin_addr);
    socket_list = push_socket(socket_list, sockfd, ip);

    if (death > -1)
        socket_list = push_socket(socket_list, death, extra_ip);
    
    while (42) 
    {
        memset(fds, 0, sizeof(fds));
        pollfd_list = 0;
        reset_pollfds_list(socket_list);
        int x = 0;
        while (x < pollfd_list) {
            printf("fd : %d\n", fds[x].fd);
            x++;
        }
        print_linked_list(socket_list);
        trigger =  poll(fds, pollfd_list, 100000);
        if (trigger) {
            checking_polling_list(sockfd, fds[0].fd,socket_list );
            if (fds[0].revents & POLLIN) {  
                if (client_type == CLIENT)
                    newsock = accept_new_connection(client_side, socket_address);
                else
                    newsock = accept_new_connection(sockfd, socket_address);
                if (newsock) {

                    printf("NEW SOCKET\n");
                    if (user_access_or_node(newsock, SERVER, -1) == true)
                    {
	                    remote_filesys = handshake(newsock, SERVER);
                        //remote_filesys = handshake(newsock, SERVER);
                        broadcast_new_node(remote_filesys, socket_list, newsock, fds[0].fd);
                    } 
                    ip = inet_ntoa(socket_address.sin_addr);
                    socket_list = push_socket(socket_list, newsock, ip);
                }
            }
        }
    }


}











