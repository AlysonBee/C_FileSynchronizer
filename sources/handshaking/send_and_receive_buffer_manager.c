

#include "../../includes/file_sync.h"

void		send_loop(int sockfd, unsigned char *buffer_to_send, int type)
{
	uint64_t		buffer_size;
	unsigned char	*buffer_size_info;
	int32_t			first_chunk_size;

	printf("sending...\n");
	first_chunk_size = MAGIC_NUMBER_SIZE + sizeof(int64_t);
	buffer_size_info = (unsigned char *)malloc(sizeof(unsigned char) *
		first_chunk_size);
	bzero(buffer_size_info, first_chunk_size);
	memcpy(buffer_size_info, buffer_to_send, first_chunk_size);
	if (type)
		memset(&buffer_size_info[first_chunk_size], '\0',  first_chunk_size);
	DEBUG_BUFFER(buffer_size_info, first_chunk_size * 2);
	send(sockfd, buffer_size_info, first_chunk_size,  0);

}

static void	retry_recv(int sockfd, unsigned char **buffer_size_info,
	int32_t first_chunk_size, int32_t retries)
{
	int32_t	i;

	i = 0;
	while (i < retries)
	{
		read(sockfd, *buffer_size_info, first_chunk_size);
		i++;
	}
	memset(*buffer_size_info + first_chunk_size, '\0', first_chunk_size);
}

int64_t		get_buffer_size_for_recv(unsigned char *size_information)
{
	int32_t			counter;
	bool			found;
	unsigned char	*trust_key;
	int64_t			file_sizes;

	counter = 0;
	found = false;

	while (counter < (MAGIC_NUMBER_SIZE + sizeof(int64_t)) * 2)
	{
		if (size_information[counter] != 0)
		{
			found = true;
			break;
		}
		counter++;
	}
	size_information += counter;
	trust_key = (unsigned char *)malloc(sizeof(unsigned char) *
		MAGIC_NUMBER_SIZE);
	memcpy(trust_key, size_information, MAGIC_NUMBER_SIZE);
	
	size_information += MAGIC_NUMBER_SIZE;
	file_sizes = extract_number_from_buffer(size_information);
	
	printf("fiel sizes is %ld\n", file_sizes);
	return (file_sizes);
}




unsigned char		*recv_loop(int sockfd, int type)
{
	unsigned char	*buffer_size_info;
	int32_t			first_chunk_size;
	
	printf("receiving...\n");
	first_chunk_size = MAGIC_NUMBER_SIZE + sizeof(int64_t);
	buffer_size_info = (unsigned char *)malloc(sizeof(unsigned char) * first_chunk_size);
	bzero(buffer_size_info, sizeof(first_chunk_size));
	retry_recv(sockfd, &buffer_size_info, first_chunk_size, 2);
	return (buffer_size_info);
}

unsigned char		*send_and_receive_manager(int sockfd, int client_type,
	t_local_file_list *transmission_buffer)
{
	unsigned char	*buffer_to_send;
	int64_t			recv_buffer_size;
	unsigned char	*received_buffer;
	unsigned char	*remote_filesystem;

	if (client_type == CLIENT)
	{
		printf("CLIENT\n");
		buffer_to_send = serialize_transmission_buffer(transmission_buffer);
		printf("Sending payload...\n");
		send_loop(sockfd, buffer_to_send, CLIENT);

		sleep(5);
		received_buffer = recv_loop(sockfd, CLIENT);
		printf("CURRENT BUFFER : ");
		DEBUG_BUFFER(received_buffer, 40);
		recv_buffer_size = get_buffer_size_for_recv(received_buffer);
		
		send(sockfd, buffer_to_send, recv_buffer_size * 2, 0);
		sleep(5);
		remote_filesystem = (unsigned char*)malloc(sizeof(unsigned char) *
			recv_buffer_size * 512);
		sleep(5);
		recv(sockfd, remote_filesystem, recv_buffer_size * 2, 0);
	}
	else
	{
		sleep(5);
		printf("SERVER\n");
		printf("Receiving payload...\n");
		received_buffer = recv_loop(sockfd, SERVER);
		
		printf("Sending payload...\n");
		printf("CURRENT BUFFER : ");
		DEBUG_BUFFER(received_buffer, 40);
		buffer_to_send = serialize_transmission_buffer(transmission_buffer);
		send_loop(sockfd, buffer_to_send, SERVER);
	
		recv_buffer_size = get_buffer_size_for_recv(received_buffer);
	
		sleep(5);
		remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
			* recv_buffer_size + 512);

		send(sockfd, buffer_to_send, recv_buffer_size + 512, 0);
	
		sleep(5);	
		recv(sockfd, remote_filesystem, recv_buffer_size + 512, 0);
	//	send(sockfd, buffer_to_send, recv_buffer_size + 512, 0);
	}
//	DEBUG_BUFFER(remote_filesystem, recv_buffer_size);

	return (remote_filesystem);
}	



