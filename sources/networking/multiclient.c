

#include "../../includes/file_sync.h"


void            broadcast_new_node(unsigned char *remote_filesys, socket_t *socket_list,
        int new_socket, int this_server_sock) 
{
    socket_t    *current_socket;

    current_socket = socket_list;
    while (current_socket) 
    {
        if (current_socket->sockfd == new_socket ||
            current_socket->sockfd == this_server_sock) 
        {
           current_socket = current_socket->next;
           continue;
        }

        if (current_socket->sync == true)
            broadcast_send(current_socket->sockfd, remote_filesys);

        current_socket = current_socket->next;
    }
}

void            broadcast_message(int transmitter, int this_socket, socket_t *sockets,
        unsigned char *remote_filesys) 
{
    socket_t *current;

    current = sockets;
    while (current) 
    {
        if (current->sockfd == this_socket || current->sockfd == transmitter) 
        {
            current = current->next;
            continue ;
        }
        broadcast_send(current->sockfd, remote_filesys);
        current = current->next;
    }
}



