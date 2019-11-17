

#include "../../includes/file_sync.h"


void    broadcast_send(unsigned char *transmission_buffer, int sockfd)
{
    uint64_t    buffer_size;
    unsigned char   *number_to_send;
        
    buffer_size = total_file_size(transmssion_buffer);
    number_to_send = uitoa(buffer_size);
    send(sockfd, number_to_send, strlen(number_to_send) + 1, 0);
    controlled_send(sockfd, transmission_buffer, buffer_size);

}   


void    broadcast_recv(unsigned char *transmission_buffer, int sockfd)
{
    uint64_t    buffer_size;
    unsigned char   buffer[4096];
    uint64_t    number;
    unsigned char   *remote_filesystem;


    bzero(buffer, 4096);
    recv(sockfd, buffer, 4096);
    number = atoi((unsigned char *)buffer);
    remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char) *
        number + 1);
    controlled_recv(sockfd, remote_filesystem, number);
}

