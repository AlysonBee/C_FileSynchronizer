


#include "../../includes/file_sync.h"

bool		check_folder_path_exists(char *directory_name)
{
	DIR		*dp;

	dp = opendir(directory_name);
	if (dp)
	{
		closedir(dp);
		return (true);
	}
	return (false);
}


void		directory_path_management(t_file_list *file_info)
{
	char		*directory_name;
	uint64_t	counter;

	counter = 0;
	while (file_info->filename[counter])
	{
		if (file_info->filename[counter] == '/')
		{
			directory_name = sub(file_info->filename, 0, counter);
			if (check_folder_path_exists(directory_name) == false)
			{
				printf(">");
			//  printf("CREATING %s\n", directory_name);
				mkdir(directory_name, 0755);
			//	create_subdirectory(counter, file_info);
			}
		}
		counter++;
	}
}

void			write_file_content(t_file_list *file_to_change)
{
	int 		fd;
	
	fd = open(file_to_change->filename, O_RDWR | O_CREAT, 0755);
	write(fd, file_to_change->file_content, file_to_change->filesize);
	close(fd);
}

void		    overwrite_older_file_version(t_file_list *file_to_change)
{	
	if (strchr(file_to_change->filename, '/'))
	{
		directory_path_management(file_to_change);
	}
//	printf("CREATING FILE : %s\n", file_to_change->filename);
	write_file_content(file_to_change);
}

void			resolve_file_conflicts(unsigned char *remote_file_system)
{
	t_file_list		*remote_node_file_list;
	t_file_list		*traverse_list;
	time_t			local_timestamp;
	int				counter;

	counter = 0;
	remote_node_file_list = deserialize_transmission_buffer(
		remote_file_system
	);
	traverse_list = remote_node_file_list;
	//:print_file_list(traverse_list);
	while (traverse_list)
	{
		if (!isprint(traverse_list->filename[0]))
		{
			traverse_list = traverse_list->next;
			continue ;
		}
		counter++;
		if (access(traverse_list->filename, F_OK) != -1)
		{
			local_timestamp = extract_file_timestamp(traverse_list->filename);
			if (local_timestamp != traverse_list->timestamp)
			{
				if (local_timestamp > traverse_list->timestamp)
				{
					printf("OVERWRITE THIS VERSION\n");
					overwrite_older_file_version(traverse_list);
				}
			}
		}
		else
		{
			overwrite_older_file_version(traverse_list);
		}
		traverse_list = traverse_list->next;
	}
}
