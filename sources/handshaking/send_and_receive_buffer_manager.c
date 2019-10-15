

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

static void			controlled_send(int sockfd, unsigned char *buffer,
	int64_t byte_size)
{
	uint64_t		size;
	uint64_t		max;
	char			halt[3];
	
	max = 0;
	size = 0;
	max = byte_size;
	while (byte_size > 0)
	{
		printf("send\n");
		send(sockfd, buffer, 2500, 0);
		DEBUG_BUFFER(buffer, 2500);
		sleep(1);
		max++;
		byte_size -= 2500;
		size += 2500;
		buffer += 2500;
		if (byte_size - 2500 < 0)
		{
			send(sockfd, buffer, byte_size, 0);
			break;
		}
	//	printf("recv\n");
	//	recv(sockfd, halt, 500, 0);
	}
}

static void			controlled_recv(int sockfd, unsigned char *buffer,
	int64_t byte_size)
{
	uint64_t	size;
	uint64_t	max;

	max = 0;
	size = 0;
	unsigned char *ptr;
	ptr = buffer;
	while (byte_size > 0)
	{
		printf("recv\n");
		recv(sockfd, buffer, 2500, 0);
		DEBUG_BUFFER(buffer, 2500);
		sleep(1);
		byte_size -= 2500;
		buffer += 2500;
		size += 2500;
		if (byte_size - 2500 < 0)
		{
			recv(sockfd, buffer, byte_size, 0);
			break;
		}
	//	buffer += size;
		max++;
		printf("%zu left\n", byte_size);
	}
	DEBUG_BUFFER(ptr, 100000);
}



static uint64_t		send_incoming_buffer_size(int sockfd, unsigned char *buffer,
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
		int j = 0;
		while (j < 40)
		{
			if (isprint(number_storage[j]))
				printf("%c", number_storage[j]);
			j++;
		}
		printf("\n");
		while (i < 20)
		{
			printf("%d-%d\n", i, number_storage[i]);
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
		printf("size is %zu\n", size);
		local_buffer_size = total_file_size(buffer_to_send);
		printf("sending\n");
		sleep(5);
		controlled_send(sockfd, buffer_to_send, local_buffer_size);
		printf("size is %zu\n", size);
	//	send(sockfd, buffer_to_send, local_buffer_size, 0);
		printf("Sent\n\n\n\n\n\n\n\n");
	//	DEBUG_BUFFER(buffer_to_send, local_buffer_size);	
		
		sleep(5);
		remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
			* size * 2);
		controlled_recv(sockfd, remote_filesystem, size);
		printf("\n\n\n\n\n\n\n\n\n");
	//	DEBUG_BUFFER(remote_filesystem, size);
		printf(" DDDD %zu\n", size);
		printf("CLIENT\n");
	}
	else
	{
		buffer_to_send = serialize_transmission_buffer(transmission_buffer);
		size = send_incoming_buffer_size(sockfd, buffer_to_send, SERVER);
		printf("size is %lld\n", size);	
		remote_filesystem = (unsigned char *)malloc(sizeof(unsigned char)
			* size * 2);
		bzero(remote_filesystem, size * 2);	
		head_ptr = remote_filesystem;
		printf("REceiving...\n");

	//	recv(sockfd, remote_filesystem, size, 0);	
		controlled_recv(sockfd, remote_filesystem, size);
		printf("RECVIED..............\n\n\n");
	//	DEBUG_BUFFER(head_ptr, size);

		sleep(5);
		local_buffer_size = total_file_size(buffer_to_send);
		controlled_send(sockfd, buffer_to_send, local_buffer_size);
		printf("SERVER\n");
		printf("\n\n\n\n\n\n\n\n");
		DEBUG_BUFFER(buffer_to_send, local_buffer_size);
		printf("%zu\n", size);
	}
//	DEBUG_BUFFER(remote_filesystem, recv_buffer_size);
//	exit(1);
	return (remote_filesystem);


}	



