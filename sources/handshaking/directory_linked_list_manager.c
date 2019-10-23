

#include "../../includes/file_sync.h"

void        free_directory_list(t_dir *directory_list)
{
    t_dir   *traverse;

    while (directory_list)
    {
        traverse = directory_list;
        directory_list = directory_list->next;
        free(traverse->directory_name);
        free(traverse);
    }
}

t_dir		*new_directory(char *directory_name)
{
	t_dir	*head;

	head = (t_dir *)malloc(sizeof(t_dir));
	head->directory_name = strdup(directory_name);
	head->next = NULL;
	return (head);
}

t_dir	*add_directory(t_dir *head, char *directory_name)
{
	t_dir	*traverse_list;

	traverse_list = head;
	while (traverse_list->next)
		traverse_list = traverse_list->next;
	traverse_list->next = (t_dir *)malloc(sizeof(t_dir));
	traverse_list->next->directory_name = strdup(directory_name);
	traverse_list->next->next = NULL;
	return (traverse_list);
}

t_dir	*create_and_add_directory(t_dir *head, char *directory_name)
{
	t_dir	*traverse_list;

	traverse_list = head;
	if (traverse_list == NULL)
	{
		head = new_directory(directory_name);
	}
	else
	{
		traverse_list = add_directory(head, directory_name);
		traverse_list = head;	
	}
	return (head);
}
