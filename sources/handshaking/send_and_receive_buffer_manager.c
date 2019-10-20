

#include "../../includes/file_sync.h"

void			controlled_send(int sockfd, unsigned char *buffer,
	int64_t byte_size)
{
	ssize_t		size;
	
	
	size = 0;
	while (byte_size > 0)
	{
		size = send(sockfd, buffer, 2500, 0);
//		sleep(1);
		byte_size -= size;//2500;
		//size += 2500;
		buffer += size;//2500;
		if (byte_size - size < 0)
		{
			send(sockfd, buffer, byte_size, 0);
			break;
		}
	}
}

void			controlled_recv(int sockfd, unsigned char *buffer,
	int64_t byte_size)
{
	ssize_t	size;

	size = 0;
	while (byte_size > 0)
	{
		size = recv(sockfd, buffer, 2500, 0);
	//	sleep(1);
		byte_size -= size;//2500;
		buffer  += size; //2500;
	//	size += 2500;
		if (byte_size - size < 0)
		{
			recv(sockfd, buffer, byte_size, 0);
			break;
		}
	}
    printf("====================\n");
    DEBUG_BUFFER(buffer, 200);
}



uint64_t		send_incoming_buffer_size(int sockfd, unsigned char *buffer,
	int type)
{
	uint64_t		buffer_size;
	ssize_t			size;
	char			*buffer_content;
	char			number_storage[4096];
	int				i;
	i = 0;
	
	buffer_size = total_file_size(buffer);
	buffer_content = itoa(buffer_size);
	if (type == SERVER)
	{
		send(sockfd, buffer_content, strlen(buffer_content) + 1, 0);
		sleep(5);
		size = recv(sockfd, number_storage, 4096, 0);
		while (i < 20)
		{
			if (isdigit(number_storage[i]))
				break;
			i++;
		}
	}
	else
	{
		sleep(1);
		size = recv(sockfd, number_storage, 4096, 0);
		while (i < 20)
		{
			if (isdigit(number_storage[i]) && number_storage[i] - 48 > 0)
				break;
			i++;
		}
		send(sockfd, buffer_content, strlen(buffer_content) + 1, 0);
	}
	return ((uint64_t)atoi(&number_storage[i]));
}



unsigned char		*send_and_receive_manager(int sockfd, int client_type,
	t_local_file_list *transmission_buffer)
{
	unsigned char	*buffer_to_send;
	int64_t			size;
	unsigned char	*received_buffer;
	unsigned char	*remote_filesystem;
	int64_t			local_buffer_size;
	unsigned char	*head_ptr;

	if (client_type == CLIENT)
	{
		buffer_to_send = serialize_transmission_buffer(transmission_buffer);
		size = send_incoming_buffer_size(sockfd, buffer_to_send, CLIENT);
		local_buffer_size = total_file_size(buffer_to_send);
		sleep(5);
		controlled_send(sockfd, buffer_to_send, local_buffer_size);
		
		sleep(5);
		remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
			* size * 2);
		controlled_recv(sockfd, remote_filesystem, size);
	}
	else
	{
		buffer_to_send = serialize_transmission_buffer(transmission_buffer);
		size = send_incoming_buffer_size(sockfd, buffer_to_send, SERVER);
		remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
			* size * 2);
		bzero(remote_filesystem, size * 2);	

		head_ptr = remote_filesystem;
		controlled_recv(sockfd, remote_filesystem, size);

		sleep(5);
		local_buffer_size = total_file_size(buffer_to_send);
		controlled_send(sockfd, buffer_to_send, local_buffer_size);
	}
	return (remote_filesystem);
}


