
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
        malloc_size = (uint64_t)atoi(recv_buffer);

        buffer = (unsigned char *)malloc(sizeof(unsigned char) * malloc_size);
        sleep(1);
        controlled_recv(sockfd, buffer, malloc_size);
    return (buffer);
}


void        deletion_loop(char *storage_buffer)
{
    char    **file_list;
    int32_t counter;
    struct stat info;
    char    **filename;

    counter = 0;
    file_list = ft_strsplit(storage_buffer, ',');
    if (file_list == NULL)
        return ;
    while (file_list[counter + 1])
    {
        if (strchr(file_list[counter], ':') == NULL)
        {
            counter++;
            continue ;
        }
        filename = ft_strsplit(file_list[counter], ':');
        stat(filename[1], &info);
         
        if (S_ISDIR(info.st_mode))
            remove_directory(&file_list[counter][4]);
        else
            remove(&file_list[counter][4]);
        counter++;
        free2d(filename);
    }
    //    free2d(file_list);
}

void        daemon_recv_process(int sockfd)
{
    unsigned char   *storage_buffer;
    t_file_list     *deserialize;
    int             fd;
    t_file_list     *traverse;
    extern t_lst     *HASH;


    storage_buffer = recv_remote_buffer_size(sockfd);
    if (strstr((char *)storage_buffer, "del:"))
    {
        printf("DELETING\n");
        deletion_loop((char *)storage_buffer);
        g_coordinate = strdup("DONE");
    }
    else
    {
        printf("UPDATING\n");
        deserialize = deserialize_transmission_buffer(storage_buffer);
        printf("Deserialize : \n");
        traverse = deserialize;
        while (traverse)
        {

            if (strchr(traverse->filename, '/'))
                directory_path_management(traverse);
            fd = open(traverse->filename, O_RDWR | O_CREAT | O_TRUNC, 0755);
            write(fd, traverse->file_content, traverse->filesize);
            traverse = traverse->next;
        }
        g_coordinate = strdup("DONE\n");
        free_file_list_node(deserialize);
        printf("============================\n");
    }
}
