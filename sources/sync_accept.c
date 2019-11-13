


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

t_id        *sync_accept(int sockfd, t_id *file_list, struct sockaddr_in socket_address,
        int server_socket)
{
    int         accept_socket;
    socklen_t   length;
    t_id        *traverse_ids;

    length = sizeof(socket_address);
    accept_socket = accept(sockfd, (struct sockaddr *)&socket_address,
        &length);

    file_list = socket_id_list_manager(file_list, accept_socket, "NULL");
   
    unsigned char *remote_filesystem = NULL;
    remote_filesystem = handshake(accept_socket, SERVER);

    traverse_ids = file_list;
    
    
   
    DEBUG_BUFFER(remote_filesystem, 300);
    /*}
    size_t remote_filesys_size = total_file_size(remote_filesystem);
  

    printf("filesys size : %zu\n", remote_filesys_size); 
    char *number_string = uitoa(remote_filesys_size);

    printf("number string : %s\n", number_string);
    ssize_t s = send(server_socket, number_string, strlen(number_string) + 1, 0);

    printf("byte count : %zu\n", s); 
    */
    

    while (traverse_ids)
    {
        if (traverse_ids->sockfd && traverse_ids->sockfd != accept_socket)
        {
            printf("id is : %d\n", traverse_ids->sockfd);
           
            handshake(traverse_ids->sockfd, CLIENT);
            /*
            size_t remote_filesys_size = total_file_size(remote_filesystem);
            printf("MAX FILESYS SIZE %zu\n", remote_filesys_size);
            char *number_string = uitoa(remote_filesys_size); 
            printf("number string %s\n", number_string);
            printf("send to %d\n", traverse_ids->sockfd);
            //send_incoming_buffer_size(*file_list[counter], remote_filesystem, SERVER);
            ssize_t s= send(server_socket, number_string, strlen(number_string) + 1, 0);
            printf("sent string to id : byte count %zu\n", s);
            sleep(2);
            controlled_send(server_socket, 
                  remote_filesystem,
                  total_file_size(remote_filesystem)
            );  */
        }
       // file_list = socket_id_list_manager(file_list, accept_socket, "NULL");
        traverse_ids = traverse_ids->next;
    }
    return (file_list);
}







