


#include "../includes/file_sync.h"


static void DEBUG_2DARRAY(t_id *file_list)
{
    t_id    *traverse;

    traverse = file_list;
    while (traverse)
    {
        printf("i is %d\n", traverse->sockfd);
        traverse = traverse->next;
    }
}

void       sync_accept(int sockfd, t_id *file_list, struct sockaddr_in socket_address)
{
    int         accept_socket;
    socklen_t   length;
    t_id        *traverse_ids;

    length = sizeof(socket_address);
    accept_socket = accept(sockfd, (struct sockaddr *)&socket_address,
        &length);

    file_list = socket_id_list_manager(file_list, accept_socket, "NULL");
   

    unsigned char *remote_filesystem = NULL;
    // remote_filesystem = handshake(accept_socket, SERVER);

    traverse_ids = file_list;
    while (traverse_ids)
    {
        if (traverse_ids->sockfd && traverse_ids->sockfd != accept_socket)
        {
            size_t remote_filesys_size = total_file_size(remote_filesystem);
            char *number_string = uitoa(remote_filesys_size); 
            //send_incoming_buffer_size(*file_list[counter], remote_filesystem, SERVER);
            send(traverse_ids->sockfd, number_string, strlen(number_string) + 1, 0);
            sleep(2);
            controlled_send(traverse_ids->sockfd, remote_filesystem, total_file_size(remote_filesystem)); 
        }
        traverse_ids = traverse_ids->next;
    }
}







