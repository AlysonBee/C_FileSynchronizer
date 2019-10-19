

#include "../includes/file_sync.h"

t_file_list   *tf_to_file_list(t_ft *file_meta)
{
    t_file_list *head;
    t_ft        *travel;

    head = NULL;
    travel = file_meta;
    while (travel)
    {
        head = create_and_add_file_list_node(
            head,
            travel->filename,
            extract_file_size(travel->filename),
            extract_file_timestamp(travel->filename),
            extract_file_content(travel->filename) 
        );
        travel = travel->next;
    }
    return (head);
}

t_file_list    *files_are_unchanged(t_ft *starting_list,
        t_ft *current_list)
{
    t_file_list     *new_node;

    new_node = NULL;
    if (strcmp(starting_list->filename, current_list->filename) == 0)
    {
        if (starting_list->timestamp < current_list->timestamp)
        {
            new_node = new_file_list_node(
                    current_list->filename,
                    extract_file_size(current_list->filename),
                    extract_file_timestamp(current_list->filename),
                    extract_file_content(current_list->filename)
            );
        }
    }
    return (new_node);
}


t_file_list  *differences(t_ft *starting_list, t_ft *current_list)
{
    t_ft            *travel_list;
    t_ft            *current_travel_list;
    char            *filename;
    t_file_list     *new_file;

    current_travel_list = current_list;
    travel_list = starting_list;
    while (travel_list && current_travel_list)
    {
        new_file = files_are_unchanged(travel_list, current_travel_list);
        if (new_file != NULL)
            break;
        travel_list = travel_list->next;
        if (current_travel_list == NULL)
            break ;
        current_travel_list = current_travel_list->next;
    }
    if (current_travel_list)
        return (tf_to_file_list(current_travel_list));
    return (new_file);
}

void        send_updated_file(t_file_list *node_to_send, int sockfd)
{
    unsigned char       *transmission_buffer;
	uint64_t			file_size;
	int32_t				files_count;
	t_local_file_list	*transmission_buffer_template;

	unsigned char	    *buffer_to_send;
	int64_t			    size;
	int64_t			    local_buffer_size;

    files_count = number_of_files(node_to_send);
	file_size = total_of_all_file_sizes(node_to_send);

    transmission_buffer_template = (t_local_file_list *)malloc(
		sizeof(t_local_file_list));

    transmission_buffer_template->total_file_sizes = file_size;
	transmission_buffer_template->file_list = node_to_send;
	transmission_buffer_template->number_of_files = files_count; 

    transmission_buffer = serialize_transmission_buffer(
        transmission_buffer_template
    );

	buffer_to_send = serialize_transmission_buffer(transmission_buffer_template);
	local_buffer_size = total_file_size(buffer_to_send);

    /*
	sleep(5);
	controlled_send(sockfd, buffer_to_send, local_buffer_size);
    */
}

void        daemon_operation(int sockfd)
{
    t_ft        *starting_file_list;
    t_ft        *current_list;
    t_file_list *node_to_replace;

    current_list = NULL;
    starting_file_list = NULL;
    starting_file_list = inspect_directory(
        starting_file_list,
        "."
    );
    while (true)
    {
        current_list = inspect_directory(
            current_list,
            "."
        );
        node_to_replace = differences(
            starting_file_list,
            current_list
        );
        if (node_to_replace == NULL)
      
           free_file_timestamp(current_list);
        else
        {
            send_updated_file(node_to_replace, sockfd);
        }
         break ;
   }
    if (node_to_replace == NULL)
        printf("NULL\n");
    printf("Phere\n");
}















