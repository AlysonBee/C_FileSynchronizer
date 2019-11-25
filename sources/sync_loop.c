
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
    fdlist_object.revents = 0;
    fds[pollfd_list] = fdlist_object;
    pollfd_list++;
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
            

          //  if (strncmp((char *)remote_filesys, "req", 3) == 0)
          //      check_api_request(sockets, remote_filesys);
            //else 
                broadcast_message(fds[index].fd, this_socket,
                        sockets, remote_filesys);
            free(remote_filesys);
        } 
        index++; 
        
    }
    return (flag);
}


int        handle_client_side(socket_t *socket_list, int extra_socket) {

    int counter = 0;
    int flag = -1;
    unsigned char *remote_filesys;

    printf("Preemptive strike\n");

    while (counter < pollfd_list) {
        if (fds[counter].fd == extra_socket) {
            if (fds[counter].revents & POLLIN) {
                flag = 1;
                printf("handle_client_side()\n");
                remote_filesys = broadcast_recv(fds[counter].fd);
                free(remote_filesys);
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
    socket_list = push_socket(socket_list, *client_side, client_ip, true, NULL);
    return (socket_list);
}


void            sync_loop(int sockfd, int client_type, 
            struct sockaddr_in socket_address,
            int extra_sock, char *extra_ip, int usertype)
{
    int32_t         max_file_descriptor;
    int32_t         trigger;
    socket_t        *socket_list;
    int             newsock;
   
    int             death = extra_sock;
    int             client_side;
    char            *ip;
    unsigned char   *remote_filesys;
    bool            node_sync_flag;
    char            *app_name;

    socket_list = NULL;
    if (client_type == CLIENT && usertype != USERTYPE)
        socket_list = assign_client_socket(&client_side, socket_list);
    
    ip = inet_ntoa(socket_address.sin_addr);

    if (usertype == USERTYPE)
        node_sync_flag = false;
    else
        node_sync_flag = true;

    socket_list = push_socket(socket_list, sockfd, ip, node_sync_flag, NULL);

    if (death > -1 && usertype != USERTYPE)
        socket_list = push_socket(socket_list, death, extra_ip, node_sync_flag,
                NULL);
    
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
                    unsigned char buf[4096];
                    if (user_access_or_node(newsock, SERVER, -1, buf) == true)
                    {
                        node_sync_flag = true;
	                    remote_filesys = handshake(newsock, SERVER);
                        broadcast_new_node(remote_filesys, socket_list, newsock,
                                fds[0].fd);
                    }
                    else if (application_joining_network(buf) == true)
                    {
                        char *name = strchr((char *)buf, '=');
                        app_name = strdup((char *)&name[1]);
                        node_sync_flag = false;
                    }
                    else if (strncmp((char *)buf, "req", 3) == 0)
                    {
                        check_api_request(socket_list, buf, newsock);
                        continue ;
                    }
                    else
                    {
                        printf("ELSE ELSE ELS\n");
                        node_sync_flag = false; 
                    }

                    ip = inet_ntoa(socket_address.sin_addr);
                    socket_list = push_socket(socket_list, newsock, ip,
                            node_sync_flag, app_name);
                    app_name = NULL;
                }
            }
        }
    }


}











