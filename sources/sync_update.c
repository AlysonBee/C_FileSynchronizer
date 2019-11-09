
#include "../includes/file_sync.h"

unsigned char    *receive_file_content(int sockfd)
{
    unsigned char *remote_filesystem;
    char          local_buffer[4096];
    size_t        size;

	recv(sockfd, local_buffer, 4096, -1);
    size = strlen((char *)local_buffer);
    remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
		* size * 2);
    bzero(remote_filesystem, size * 2);

    controlled_recv(sockfd, remote_filesystem, size);
    return (remote_filesystem);
} 

int     sync_update(fd_set file_descriptor_list, int *file_list)
{
    int     counter;
    unsigned char    *remote_filesystem;

    counter = 0;
    while (counter < MAX_FILE_DESCRIPTOR_LIST)
    {
        if (FD_ISSET(file_list[counter], &file_descriptor_list))
        {
            remote_filesystem = receive_file_content(file_list[counter]);
            resolve_file_conflicts(remote_filesystem);
            free(remote_filesystem);
            break;
        }
        counter++;
    } 
    return (0);
}
