


#include "../includes/file_sync.h"

void	print_nodes(t_ft *head_node)
{
	t_ft	*trav;

	trav = head_node;
	while (trav)
	{
		printf("trav is %s\n", trav->filename);
		trav = trav->next;
	}
}

t_ft	*traverse_inspection(t_ft *head_node, t_dir *directory_list)
{
	t_dir	*directory_traverse;
	
	directory_traverse = directory_list;
	while (directory_traverse)
	{
		head_node = inspect_directory(head_node, directory_traverse->directory_name);
		directory_traverse = directory_traverse->next;
	}
	return (head_node);
}



t_ft	*inspect_directory(t_ft *head_node, char *directory_name)
{
	t_ft			*ft_traverse;
	t_dir			*dir_list;
	struct dirent	*directory;
	struct stat		info;
	DIR				*dp;
	char			*full_path_name;
	time_t			file_timestamp;

	dir_list = NULL;
	ft_traverse = head_node;
	dp = opendir(directory_name);
	if (dp == NULL)
		return head_node;
	while ((directory = readdir(dp)))
	{
        printf("direc: %s\n", directory->d_name);
		if (directory->d_name[0] == '.')
			continue ;
		 full_path_name = generate_path(directory_name,
			directory->d_name);
		stat(full_path_name, &info);
		if (S_ISDIR(info.st_mode))
			dir_list = create_and_add_directory(dir_list, full_path_name);
		else
		{
			file_timestamp = extract_file_timestamp(full_path_name);
			ft_traverse = create_and_add_file_timestamp(ft_traverse,
				full_path_name,
				file_timestamp);
		}	
	}
	return (traverse_inspection(ft_traverse, dir_list));
}

/*
int	main(void)
{
	t_ft	*head;

	head = NULL;
	head = inspect_directory(head, ".");
	t_ft 	*trav;
	if (head == NULL)
		printf("none\n");

	trav = head;
	while (trav)
	{
		printf("trav -> filename : %s\n", trav->filename);
		trav = trav->next;
	}
	return (0);
} */
