
#include "../includes/file_sync.h"

unsigned char    *receive_file_content(int sockfd)
{
    unsigned char *remote_filesystem;
    char          local_buffer[4096];
    size_t        size;

	recv(sockfd, local_buffer, 4096, -1);
    sleep(2);
    size = strlen((char *)local_buffer);
    remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
		* size * 2);
    bzero(remote_filesystem, size * 2);

    controlled_recv(sockfd, remote_filesystem, size);
    return (remote_filesystem);
} 

int     sync_update(fd_set file_descriptor_list, t_id *file_list)
{
    t_id    *traverse_ids;
    unsigned char    *remote_filesystem;

    traverse_ids = file_list;
    printf("sync update\n"); 
    while (traverse_ids)
    {
        if (FD_ISSET(traverse_ids->sockfd, &file_descriptor_list))
        {
            printf(" is siet \n");
            remote_filesystem = receive_file_content(traverse_ids->sockfd);
            resolve_file_conflicts(remote_filesystem);
            free(remote_filesystem);
            break;
        }
        traverse_ids = traverse_ids->next;
    } 
    return (0);
}
