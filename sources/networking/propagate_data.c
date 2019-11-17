

#include "../../includes/file_sync.h"


void    broadcast_send(int sockfd, unsigned char *buffer)
{
    uint64_t    buffer_size;
    unsigned char   *number_to_send;
    t_local_file_list   *transmission_template;

    transmission_template = (t_local_file_list *)malloc(
		sizeof(t_local_file_list));
	transmission_template->file_list = gather_all_file_info();
    transmission_template->total_file_sizes = total_of_all_file_sizes(
            transmission_template->file_list
    );
  
    transmission_template->number_of_files = number_of_files(
            transmission_template->file_list
    );
    buffer = serialize_transmission_buffer(transmission_template);

    buffer_size = total_file_size(buffer);


    
    printf("sending file size : buffer_size : %llu\n", buffer_size);
    number_to_send = (unsigned char *)uitoa(buffer_size);
    printf("sending files\n");
    send(sockfd, number_to_send, strlen((char *)number_to_send) + 1, 0);


    sleep(1);
    controlled_send(sockfd, buffer, buffer_size);
}   


unsigned char   *broadcast_recv(int sockfd)
{
    uint64_t    buffer_size;
    unsigned char   number_storage[4096];
    uint64_t    number;
    unsigned char   *remote_filesystem;

    bzero(number_storage, 4096);
    printf("before reception\n");
    recv(sockfd, number_storage, 4096, 0);
 
    int i = 0;
    while (i < 20)
    {
        if (isdigit(number_storage[i]) && number_storage[i] - 48 > 0)
            break;
        i++;
    }
    
    
    printf("size received\n");
    number = (uint64_t)atoi((char *)&number_storage[i]);
    printf("size is %llu\n", number);
    remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char) *
        number + 1);
    sleep(1);
    printf("receiving...\n");
    controlled_recv(sockfd, remote_filesystem, number);
    printf("ending\n");
    resolve_file_conflicts(remote_filesystem);
    printf("resolved\n");
}

