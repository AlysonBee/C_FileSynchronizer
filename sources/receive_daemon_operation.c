
#include "../includes/file_sync.h"
#include "../includes/daemon_process.h"

char            *g_coordinate = NULL;




unsigned char   *recv_remote_buffer_size(int sockfd)
{
    unsigned char *buffer;
    char          recv_buffer[4096];
    uint64_t      malloc_size;
    ssize_t       size;

    buffer = NULL;
    bzero(recv_buffer, 4096);
    size = recv(sockfd, recv_buffer, 4096, 0);
    DEBUG_BUFFER((unsigned char *)recv_buffer, size);
    if (isdigit(recv_buffer[0]))
    {
        malloc_size = (uint64_t)atoi(recv_buffer);
        buffer = (unsigned char *)malloc(sizeof(unsigned char) * malloc_size);
        sleep(1);
        recv(sockfd, buffer, malloc_size, 0);
    }
    else
    {
        buffer = (unsigned char *)strdup((char *)recv_buffer);
    }
    return (buffer);
}


void        daemon_recv_process(int sockfd)
{
    unsigned char   *storage_buffer;
    t_file_list     *deserialize;
    int             fd;
    t_file_list     *traverse;
    extern t_lst     *HASH;


    storage_buffer = recv_remote_buffer_size(sockfd);
    if (strncmp((char *)storage_buffer, "del:", 4) == 0)
    {
        printf("Deleting file : %s\n", &storage_buffer[4]);
        g_coordinate = strdup((char *)&storage_buffer);
    }
    else
    {
        printf("Adding/Updating\n");
        deserialize = deserialize_transmission_buffer(storage_buffer);
        traverse = deserialize;
        while (traverse)
        {
            printf("filename is being replaced %s\n", traverse->filename);
            
            if (strchr(traverse->filename, '/'))
            {
                directory_path_management(traverse);
            }
            fd = open(traverse->filename, O_RDWR | O_CREAT | O_TRUNC, 0755);
            write(fd, traverse->file_content, traverse->filesize);
            // overwrite_older_file_version(traverse);
            g_coordinate = strdup(traverse->filename);
            traverse = traverse->next;
        }
        free_file_list_node(deserialize);
        printf("============================\n");
    }
}
