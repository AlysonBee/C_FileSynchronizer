

#include "../../includes/file_sync.h"


char 	*generate_path(char *directory_name, char *filename)
{
	char	*temporary;
	char	*complete_filename;

	temporary = join(directory_name, "/");
	complete_filename = join(temporary, filename);
	free(temporary);
	return (complete_filename);
}

uint64_t		extract_file_size(char *target_file)
{
	struct stat		info;
	uint64_t		file_size;
	int				fd;

	fd = open(target_file, O_RDONLY);
	fstat(fd, &info);
	file_size = info.st_size;
	return (file_size);
}

time_t				extract_file_timestamp(char *target_file)
{
	struct stat		info;
	time_t			mtime;

	stat(target_file, &info);
	mtime = info.st_mtime;
	return (mtime);
}

unsigned char	*extract_file_content(char *target_file)
{
	unsigned char	*file_content;
	int				fd;
	struct stat		info;
	

	fd = open(target_file, O_RDONLY);
	fstat(fd, &info);
	file_content = (unsigned char *)malloc(sizeof(unsigned char) *
		info.st_size);
	read(fd, file_content, info.st_size);
	close(fd);
	return (file_content);
}


static t_file_list		*extract_file_information(char *target_file,
	t_file_list *file_list)
{
	time_t			file_timestamp;
	unsigned char	*file_content;
	uint64_t		file_size;
	
	file_timestamp = extract_file_timestamp(target_file);
	file_content = extract_file_content(target_file);
	file_size = extract_file_size(target_file);
	file_list = create_and_add_file_list_node(
		file_list,
		target_file,
		file_size,
		file_timestamp,
		file_content
	);
		
	return (file_list);
}

/* 
** Gather all files in this node.
*/

t_file_list	*recursively_traverse_directories(t_dir *header,
	t_file_list *file_list)
{
	t_dir	*traverse_list;

	traverse_list = header;
	while (traverse_list)
	{
		file_list = all_files_on_this_client(
			traverse_list->directory_name,
			file_list
		);
		traverse_list = traverse_list->next;
	}
	return (file_list);
}

t_file_list	*all_files_on_this_client(char *current_directory,
	t_file_list *file_list)
{
	struct dirent	*directory;
	DIR				*dp;
	struct stat		info;
	char			*temporary_char_variable;
	char			*full_file_path;
	t_dir			*directory_list;

	directory_list = NULL;
	temporary_char_variable = (char *)malloc(sizeof(char));
	dp = opendir(current_directory);
	if (dp == NULL)
		return NULL;
	while ((directory = readdir(dp)))
	{
		if (strcmp(directory->d_name, "..") == 0 ||
			strcmp(directory->d_name, ".") == 0 ||
			directory->d_name[0] == '.')
			continue ;

		full_file_path = generate_path(current_directory,
			directory->d_name);

		stat(full_file_path, &info);
		if (S_ISDIR(info.st_mode))
		{
			directory_list = create_and_add_directory(
				directory_list,
				full_file_path
			);
		}
		else		
			file_list = extract_file_information(
				full_file_path,
				file_list
			);
	}
	return (recursively_traverse_directories(directory_list,
		file_list));
	//return (file_list)
}

t_file_list	 *gather_all_file_info(void)
{
	t_file_list 	*file_list;

	file_list = NULL;	
	file_list = all_files_on_this_client(
		".",
		file_list
	);
	t_file_list	*trav;

	trav = file_list;
	while (trav)
	{
		printf("%s\n", trav->filename);
		trav = trav->next;
	}
	return (file_list);
}


/*
int	main(void)
{
	
	handshake(4, SERVER);
	return (0);
} */
