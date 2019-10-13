
#include "../../includes/file_sync.h"

static unsigned char *malloc_and_bzero(size_t size)
{
	unsigned char	*buffer;

	buffer = (unsigned char *)malloc(sizeof(unsigned char) * size);
	bzero(buffer, size);
	return (buffer);
}

unsigned char	*malloc_transmission_buffer(t_local_file_list *transmission_buffer_template)
{
	unsigned char	*buffer;

	buffer = malloc_and_bzero(sizeof(unsigned char) *
		(sizeof(t_transmission_head) + (sizeof(t_file_info) *
		transmission_buffer_template->number_of_files) +
		transmission_buffer_template->total_file_sizes +
			transmission_buffer_template->number_of_files));
	return (buffer);
}


static void			write_files_to_buffer(unsigned char **transmission_buffer,
	t_file_list *files_to_write)
{
	t_file_list		*traversal_pointer;
	unsigned char	*local_buffer_pointer;

	local_buffer_pointer = *transmission_buffer;
	traversal_pointer = files_to_write;
	while (traversal_pointer)
	{
		memcpy(local_buffer_pointer, traversal_pointer->filename,
			strlen(traversal_pointer->filename) + 1);
		// Shift the pointer forward by filename length + '\0' value.
		local_buffer_pointer += strlen(traversal_pointer->filename) + 1;


		memcpy(local_buffer_pointer, (void*)&traversal_pointer->filesize,
			sizeof(traversal_pointer->filesize));
		// Shift the pointer by the size/datatype of traversal_pointer->filesize.
		local_buffer_pointer += sizeof(traversal_pointer->filesize);


		memcpy(local_buffer_pointer, (void*)&traversal_pointer->timestamp,
			sizeof(traversal_pointer->timestamp));
		// Shift hte pointer by the size/datatype of the traversal_pointer->timestamp	
		local_buffer_pointer+= sizeof(traversal_pointer->timestamp);
		
		
		memcpy(local_buffer_pointer, traversal_pointer->file_content,
			traversal_pointer->filesize);
		local_buffer_pointer += traversal_pointer->filesize;
		
		traversal_pointer = traversal_pointer->next;	
	}
}


static void		write_trust_key_bytes(unsigned char *transmission_buffer,
	unsigned char *trust_key)
{
	int		counter;
	
	counter = 0;
	while (counter < MAGIC_NUMBER_SIZE)
	{
		transmission_buffer[counter] = trust_key[counter];
		printf("%x\n", trust_key[counter]);
		counter++;
	}	
}

unsigned char	*serialize_transmission_buffer(t_local_file_list *transmission_buffer_template)
{
	unsigned char *transmission_buffer;
	unsigned char *buffer_start;
	unsigned char *trust_key;

	transmission_buffer = malloc_transmission_buffer(
		transmission_buffer_template
	);
	buffer_start = transmission_buffer;


	trust_key = write_trust_key();
	write_trust_key_bytes(transmission_buffer, trust_key);
	transmission_buffer += MAGIC_NUMBER_SIZE;
	free(trust_key);		

	memcpy(transmission_buffer, (void *)&transmission_buffer_template->total_file_sizes,
		sizeof(transmission_buffer_template->total_file_sizes));
	transmission_buffer += (sizeof(transmission_buffer_template->total_file_sizes));


	memcpy(transmission_buffer, (void *)&transmission_buffer_template->number_of_files,
		sizeof(transmission_buffer_template->number_of_files));
	transmission_buffer += (sizeof(transmission_buffer_template->number_of_files));


	write_files_to_buffer(&transmission_buffer,
		transmission_buffer_template->file_list);
	

	return (buffer_start);
}
