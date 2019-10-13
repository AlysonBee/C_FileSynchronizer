

#include "../includes/file_sync.h"

void	print_file_list(t_file_list *head)
{
	t_file_list		*traverse;

	traverse = head;
	while (traverse)
	{
		printf("%s\n%lld\n%ld\n%s\n====\n",
			traverse->filename,
			traverse->filesize,
			traverse->timestamp,
			traverse->file_content
		);
		traverse = traverse->next;
	}
}

void	DEBUG_BUFFER(unsigned char *buffer_start, uint64_t byte_count)
{
	size_t			i;
	i = 0;
	while (i < byte_count)
	{
		if (isprint(buffer_start[i]))
			printf("%c", buffer_start[i]);
		else
			printf("%x", buffer_start[i]);
		i++;
	}
	printf("\n");
}

char	*parse_command_line_flags(int argc, char **argv)
{
	char			*flag_buffer;
	int				counter;

	flag_buffer = NULL;
	counter = 1;
	while (counter < argc)
	{
		if (argv[counter][0] == '-' && isalnum(argv[counter][1]))
			flag_buffer = charpush(flag_buffer, argv[counter][1]);
		counter += 1;
	}
	return (flag_buffer);
}

void	print_buffer_number(unsigned char *transmission_buffer)
{
	int64_t			number;
	unsigned char	*data  = (unsigned char *)&number;
	memcpy(data, (void *)transmission_buffer, sizeof(int64_t));
	printf("number is %lld\n", number);
}
