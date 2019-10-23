

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
    bool            flag;

    new_node = NULL;
    if (strcmp(starting_list->filename, current_list->filename) == 0)
    {
        struct stat info;

        stat(current_list->filename, &info);
        if (starting_list->timestamp < info.st_mtime)
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


int         length_tf(t_ft *listing)
{
    int     i;
    t_ft    *trav;

    trav = listing;
    i = 0;
    while (trav)
    {
        i++;
        trav = trav->next;
    }
    return (i); 
}

t_file_list  *new_file_to_create(t_ft *current_list, int new_file_counter)
{
    int             counter;
    t_ft            *traverse;

    traverse = current_list;
    counter = 0;
    while (counter < new_file_counter)
    {
        traverse = traverse->next;
        counter++;
    }
    return (tf_to_file_list(traverse));
}

t_file_list  *differences(t_ft *starting_list, t_ft *current_list)
{
    t_ft            *travel_list;
    t_ft            *current_travel_list;
    char            *filename;
    t_file_list     *new_file;
    int             original_length;

    original_length = length_tf(starting_list);
    current_travel_list = current_list;
    new_file = NULL;
    travel_list = starting_list;
    while (travel_list && current_travel_list)
    {
        new_file = files_are_unchanged(travel_list, current_travel_list);
        if (new_file != NULL)
            break;
        travel_list = travel_list->next;
        current_travel_list = current_travel_list->next;
    }
   /* if (new_file == NULL && length_tf(starting_list) < length_tf(current_list))
    {
        printf("starting is %d\n", length_tf(starting_list));
        printf("current is %d\n", length_tf(current_list));
        printf("HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        return (new_file_to_create(current_list, original_length));
    }*/
   // if (current_travel_list && new_file == NULL)
     //   return (tf_to_file_list(current_travel_list));
    if (new_file != NULL)
    {
        printf("NOT NULL\n");
        print_file_list(new_file);
    }
    return (new_file);
}

void        send_buffer_size(uint64_t file_size, int sockfd)
{
    unsigned char       *buffer;

    buffer = (unsigned char*)itoa(file_size);
    send(sockfd, buffer, strlen((char *)buffer) + 1, 0);
    free(buffer);
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
    printf("info to be sent\n");
    print_file_list(node_to_send);
    printf("\ntnes eb ot ofni\n");
    send_buffer_size(local_buffer_size, sockfd);
  //  DEBUG_BUFFER(buffer_to_send, local_buffer_size);
    sleep(1);
    send(sockfd, buffer_to_send, local_buffer_size, 0);
    free(buffer_to_send); 
    free(transmission_buffer_template);
    sleep(1);
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
        {
            free_file_timestamp(current_list);
            current_list = NULL;
            node_to_replace = NULL;
        }
        else
        {
            printf("REPLACEING \n");
            print_file_list(node_to_replace);
            printf("REPLACEING\n");
            send_updated_file(node_to_replace, sockfd);
            free_file_timestamp(starting_file_list);
            free_file_timestamp(current_list);
            starting_file_list = NULL;
            current_list = NULL;
           
            starting_file_list = inspect_directory(
                starting_file_list,
                "."
            );
            free_file_list_node(node_to_replace);
            node_to_replace = NULL;
        }
    }
}















