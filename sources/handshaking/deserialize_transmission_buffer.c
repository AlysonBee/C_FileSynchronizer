

#include "../../includes/file_sync.h"


unsigned char	*extract_trust_key(unsigned char *received_buffer)
{
	unsigned char	*trust_key;
	int32_t			counter;

	trust_key = (unsigned char *)malloc(sizeof(unsigned char) * MAGIC_NUMBER_SIZE);
	counter = 0;
	while (counter < MAGIC_NUMBER_SIZE)
	{
		trust_key[counter] = received_buffer[counter];
		counter++;
	}
	return (trust_key);
}

uint64_t		extract_number_from_buffer(unsigned char *receive_buffer)
{
	uint64_t			number;
	unsigned char	*data  = (unsigned char *)&number;
	memcpy(data, (void *)receive_buffer, sizeof(int64_t));
	return (number);
}

unsigned char	*copy_file_content(unsigned char *receive_buffer,
	uint64_t content_size)
{
	unsigned char	*content_buffer;

	content_buffer = (unsigned char *)malloc(sizeof(unsigned char) *
		content_size);
	memcpy(content_buffer, receive_buffer, content_size);
	return (content_buffer);	
}

t_file_list		*create_local_file_list(unsigned char *receive_buffer,
	int32_t number_of_files)
{
	t_file_list		*file_listing;
	int32_t			counter;
	char			*filename;
	uint64_t		filesize;
	time_t			timestamp;
	unsigned char	*file_content;

	file_listing = NULL;
	counter = 0;
	while (counter < number_of_files)
	{
		filename = strdup((char*)receive_buffer);
		receive_buffer += strlen(filename) + 1;
	
		filesize = extract_number_from_buffer(receive_buffer);
		receive_buffer += sizeof(filesize);
		
		timestamp = (time_t)extract_number_from_buffer(receive_buffer);
		receive_buffer += sizeof(timestamp);
		
		file_content = copy_file_content(receive_buffer, filesize);
		receive_buffer += filesize;
		file_listing = create_and_add_file_list_node(
			file_listing,
			filename,
			filesize,
			timestamp,
			file_content
		);

		free(filename);
		free(file_content);
		counter++;
	}

	return (file_listing);
}

t_file_list			*deserialize_transmission_buffer(unsigned char *receive_buffer)
{
	unsigned char	*trust_key;
	int64_t			total_payload_size;	
	int32_t			number_of_files;
	t_file_list		*file_listing;

	trust_key = extract_trust_key(receive_buffer);
	receive_buffer += MAGIC_NUMBER_SIZE;
	
	total_payload_size = (int32_t)extract_number_from_buffer(receive_buffer);
	receive_buffer += sizeof(total_payload_size);

	number_of_files = (int32_t)extract_number_from_buffer(receive_buffer);
	receive_buffer += sizeof(number_of_files);
	
	file_listing = create_local_file_list(receive_buffer, number_of_files);
	return (file_listing);
}
