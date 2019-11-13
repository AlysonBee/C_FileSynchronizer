

#include "../../includes/handshake.h"


static bool			assert_trust_key_is_true(unsigned char *transmission_buffer)
{
	int32_t			counter;
	unsigned char	byte_to_assert;
	int32_t			multiplier;

	counter = 0;
	multiplier = BITSHIFTING_MULTIPLIER;
	while (counter < MAGIC_NUMBER_SIZE)
	{
		byte_to_assert = MAGIC_NUMBER >> multiplier & 0x000000ff;
		if (byte_to_assert != transmission_buffer[counter])
			return (false);
		counter++;
		multiplier += BITSHIFTING_MULTIPLIER;
	}
	return (true);
}

static unsigned char	*recv_identifier_number(int sockfd)
{
	unsigned char	*receive_buffer;

	receive_buffer = (unsigned char *)malloc(sizeof(unsigned char) * 
		MAGIC_NUMBER_SIZE);
	read(sockfd, receive_buffer, MAGIC_NUMBER_SIZE);
	return (receive_buffer);
}

unsigned char	*write_trust_key(void)
{
	unsigned char	*buffer;
	int				i;
	int				multiplier;

	buffer = (unsigned char *)malloc(sizeof(unsigned char) * sizeof(uint64_t));
	i = 0;
	multiplier = BITSHIFTING_MULTIPLIER;
	while (i < MAGIC_NUMBER_SIZE)
	{
		buffer[i] = MAGIC_NUMBER >> multiplier & 0x000000ff;
		i += 1;
		multiplier += BITSHIFTING_MULTIPLIER;
	}
	return (buffer);
}


static void				send_identifier_number(int sockfd)
{
	unsigned char *trust_key;

	trust_key = write_trust_key();
	send(sockfd, trust_key, sizeof(trust_key), 0);
	free(trust_key);
}


static bool				identify_connection(int sockfd, int client_type)
{
	unsigned char *return_value;

	if (client_type == SERVER)
	{
		return_value = recv_identifier_number(sockfd);
		if (assert_trust_key_is_true(return_value) == false)
			return (false);
		send_identifier_number(sockfd);
	}
	else
	{	
		send_identifier_number(sockfd);	
		return_value = recv_identifier_number(sockfd);
		if (assert_trust_key_is_true(return_value) == false)
			return (false);
	}
	free(return_value);
	return (true);
}

unsigned char	        *handshake(int sockfd, int client_type)
{
	t_file_list			*file_list;
	uint64_t			total_file_size;
	int32_t				files_count;
	t_local_file_list	*transmission_buffer_template;	
	unsigned char		*remote_filesystem;	

	//identify_connection(sockfd, client_type);
	file_list = gather_all_file_info();
	files_count = number_of_files(file_list);
	total_file_size = total_of_all_file_sizes(file_list);

	transmission_buffer_template = (t_local_file_list *)malloc(
		sizeof(t_local_file_list));

	transmission_buffer_template->total_file_sizes = total_file_size;
	transmission_buffer_template->file_list = file_list;
	transmission_buffer_template->number_of_files = files_count;
	
	remote_filesystem = send_and_receive_manager(sockfd, client_type,
		transmission_buffer_template);

	resolve_file_conflicts(remote_filesystem);

	return remote_filesystem;
}

