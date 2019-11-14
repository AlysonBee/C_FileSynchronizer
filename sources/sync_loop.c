
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
    struct socket_list *next;
}   socket_t;

socket_t *new_socket(int sockfd) {
    socket_t *new_sock;

    new_sock = (socket_t *)malloc(sizeof(socket_t));
    new_sock->sockfd = sockfd;
    new_sock->next = NULL;
    return (new_sock);
}

socket_t *add_socket(socket_t *head, int sockfd) {
    socket_t *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = (socket_t *)malloc(sizeof(socket_t));
    trav->next->sockfd = sockfd;
    trav->next->next = NULL;
    return (trav);
}

bool    does_number_exist(socket_t *head, int to_push) {
    socket_t *current;

    current = head;
    while (current) {
        if (to_push == current->sockfd)
            return true;
    }
    return false;
}

socket_t *push_socket(socket_t *head, int sockfd) {
    socket_t *trav;

    trav = head;
    if (trav == NULL)
        head = new_socket(sockfd);
    else {
     //   if (does_number_exist(head, sockfd) == true)
       //     return (head);
        trav = add_socket(head, sockfd);
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



void   broadcast_message(int transmitter, int this_socket, socket_t *sockets) {
    socket_t *current;

    current = sockets;
    while (current) {
        if (current->sockfd == this_socket || current->sockfd == transmitter) {
            current = current->next;
            continue ;
        }
        handshake(current->sockfd, SERVER);
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
            //ssize_t size = read(fds[index].fd, buffer, 4096);
           // DEBUG_BUFFER((unsigned char *)buffer, size);
            printf("checking_polling_list ()\n");
            handshake(fds[index].fd, CLIENT);
            flag = fds[index].fd;
            
           broadcast_message(fds[index].fd, this_socket, sockets);
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
        handshake(current_socket->sockfd, SERVER);
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
                handshake(fds[counter].fd, CLIENT);
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


void            sync_loop(int sockfd, int client_type, struct sockaddr_in socket_address,
        int extra_sock)
{
    int32_t max_file_descriptor;
    int32_t trigger;
     socket_t *socket_list;
    int newsock;

   int death = extra_sock;
    socket_list = NULL;
    int client_side; 
    if (client_type == CLIENT) {
        create_client_side_server(&client_side);
        socket_list = push_socket(socket_list, client_side);
        extra_sock = client_side;
       
    }
    socket_list = push_socket(socket_list, sockfd);
    if (death > -1)
        socket_list = push_socket(socket_list, death);
    //socket_list = push_socket(socket_list, sockfd);
    int flag = -1;
    while (42) 
    {
        if (client_type == CLIENT)
        printf("serverside socket is %d\n", client_side);
        memset(fds, 0, sizeof(fds));
        pollfd_list = 0;
        reset_pollfds_list(socket_list);
        /*if (client_type == CLIENT) {
            fds[0].fd = client_side;
        }*/
        printf("polling...\n");
        int x = 0;
        while (x < pollfd_list) {
            printf("fd : %d\n", fds[x].fd);
            x++;
        }
        print_linked_list(socket_list);
        trigger =  poll(fds, pollfd_list, 100000);
        if (trigger) {
            
            if (client_type == CLIENT && flag == -1) {
                flag = handle_client_side(socket_list, sockfd);
            }

          /*  if (flag == -1) {
                flag = 1;
                printf("CONTINUING\n");
                continue ;
            } */

            printf("fds[0] is %d\n", fds[0].fd);
            checking_polling_list(sockfd, fds[0].fd,socket_list );
            if (fds[0].revents & POLLIN) {
                printf("socket event\n");
                printf("fd 0 is %d\n", fds[0].fd);
                if (client_type == CLIENT)
                    newsock = accept_new_connection(client_side, socket_address);
                else
                    newsock = accept_new_connection(sockfd, socket_address);
                if (newsock) {
                    printf("heere\n");
                    printf("MAIN\n"); 

                    unsigned char *remote_filesys = handshake(newsock, SERVER);

                   // read(newsock, remote_filesys, 4096);

                    printf("AGAIN\n");

                    // TODO : TEST THIS
                    broadcast_new_node(remote_filesys, socket_list, newsock, fds[0].fd);

                    socket_list = push_socket(socket_list, newsock);
                    printf("=======================================\n");
                }
            } /* else {
                printf("ELSE CHECK POLLING\n");
                checking_polling_list(sockfd);
            } */
            flag = -1;
        }
    }


}











