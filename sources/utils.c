
#include <sys/mman.h>
#include "../includes/file_sync.h"



char    *command_shell(void)
{
    char buffer[4096];

    printf("command_shell \n");
    while (true)
    {
        bzero(buffer, 4096);
        write(1, "Node type:", 10);
        read(0, buffer, 4096);
        if (strlen(buffer) == 0)
        {
            continue;
        }
        else if (strncmp(buffer, "API", 3) == 0)
            return (strdup("API"));
        else if (strncmp(buffer, "USER", 4) == 0)
            return (strdup("USER"));
        else
            printf("Invalid shell command\n");
    }
}


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

void	DEBUG_BUFFER_TO_FILE(unsigned char *buffer_start, uint64_t byte_count,
	char *filename)
{
	size_t			i;
	FILE			*fp;

	fp = fopen(filename, "ab+");
	i = 0;
	while (i < byte_count)
	{
		if (isprint(buffer_start[i]))
			printf("%c", buffer_start[i]);
		else
			printf("%x", buffer_start[i]);
		i++;
	}
	fclose(fp);
}


uint64_t	total_file_size(unsigned char *buffer)
{
	uint64_t	counter;
	int			magic_number_counter;

	magic_number_counter = 0;
	counter = 0;
	while (magic_number_counter < 3)
	{
		if (buffer[counter] == 0x44 &&
			buffer[counter + 1] == 0x55 &&
			buffer[counter + 2] == 0x66 &&
			buffer[counter + 3] == 0x77)
			{
                printf("magic number found\n");
				break;
				magic_number_counter++;
			}
		counter++;
	}
	return (counter);
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

bool    diff_detector(char *filename1, char *filename2)
{
    size_t          sizes;
    size_t          size1;
    size_t          size2;
    unsigned char   *file1_content;
    unsigned char   *file2_content;
    bool            flag;

    map_file(&file1_content, &size1, filename1);
    map_file(&file2_content, &size2, filename2);
    if (size1 != size2)
    {
        munmap(file1_content, size1);
        munmap(file2_content, size2);
        return (false);
    }
    sizes = 0;
    while (sizes < size1)
    {
        if (filename1[sizes] != filename2[sizes])
        {
            flag = false;
            break;
        }
        sizes++;
    }
    munmap(file1_content, size1);
    munmap(file2_content, size2);
    return (true);
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
