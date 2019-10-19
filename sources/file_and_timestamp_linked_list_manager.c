

#include "../includes/file_sync.h"


t_ft	*new_file_and_timestamp(char *filename, time_t timestamp)
{
	t_ft	*ft_new;

	ft_new = (t_ft *)malloc(sizeof(t_ft));
	ft_new->filename = strdup(filename);
	ft_new->timestamp = timestamp;
	ft_new->to_send = false;
	ft_new->next = NULL;
	return (ft_new);
}

t_ft	*add_file_and_timestamp(t_ft *head_node, char *filename,
	time_t timestamp)
{
	t_ft	*ft_traverse;

	ft_traverse = head_node;
	while (ft_traverse->next)
		ft_traverse = ft_traverse->next;
	ft_traverse->next = (t_ft *)malloc(sizeof(t_ft));
	ft_traverse->next->filename = strdup(filename);
	ft_traverse->next->timestamp = timestamp;
	ft_traverse->next->to_send = false;
	ft_traverse->next->next = NULL;
	return (ft_traverse);
}

void    free_file_timestamp(t_ft *head_node)
{
    t_ft    *travel;

    while (head_node)
    {
        travel = head_node;
        free(head_node->filename);
        head_node = head_node->next;
        free(travel);
    }
}

t_ft	*create_and_add_file_timestamp(t_ft *head_node,
	char *filename, time_t timestamp)
{
	t_ft	*ft_traverse;

	ft_traverse = head_node;
	if (ft_traverse == NULL)
	{
		head_node = new_file_and_timestamp(filename, timestamp);
	}
	else
	{
		ft_traverse = add_file_and_timestamp(head_node, filename,
			timestamp);
		ft_traverse = head_node;
	}
	return (head_node);
} 
