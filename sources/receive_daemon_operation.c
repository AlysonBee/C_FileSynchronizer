
#include "../includes/file_sync.h"


unsigned char   *recv_remote_buffer_size(int sockfd)
{
    unsigned char *buffer   ;
    char          recv_buffer[4096];
    uint64_t      malloc_size;

    bzero(recv_buffer, 4096);
    recv(sockfd, recv_buffer, 4096, 0);

    printf("reciv buffer is %s\n", recv_buffer);
    malloc_size = (uint64_t)atoi(recv_buffer);
    buffer = (unsigned char *)malloc(sizeof(unsigned char) * malloc_size);

    printf("malloc_size is %d\n", malloc_size);
    sleep(1);
    printf("RECEIVING..\n");
  //  controlled_recv(sockfd, buffer, malloc_size);
    recv(sockfd, buffer, malloc_size, 0);
    printf("===========================\n");
    DEBUG_BUFFER(buffer, malloc_size);
    return (buffer);
}

void        daemon_recv_process(int sockfd)
{
    unsigned char   *storage_buffer;

    storage_buffer = recv_remote_buffer_size(sockfd);

    printf("============================\n"); 
}
