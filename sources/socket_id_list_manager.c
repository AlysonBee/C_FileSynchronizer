

#include "../includes/file_sync.h"


t_id        *new_socket_id(int sockfd, char *address)
{
    t_id    *new_socket_id;

    new_socket_id = (t_id *)malloc(sizeof(t_id));
    new_socket_id->sockfd = sockfd;
    new_socket_id->address = strdup(address);
    new_socket_id->next = NULL;
    return (new_socket_id);
}

t_id        *add_socket_id(t_id *head_socket_id, int sockfd, char *address)
{
    t_id    *traverse_ids;

    traverse_ids = head_socket_id;
    while (traverse_ids->next)
        traverse_ids = traverse_ids->next;

    traverse_ids->next = (t_id *)malloc(sizeof(t_id));
    traverse_ids->next->sockfd = sockfd;
    traverse_ids->next->address = strdup(address);
    traverse_ids->next->next = NULL;
    return (traverse_ids);
}

t_id        *socket_id_list_manager(t_id *head_socket_id, int sockfd, char *address)
{
    t_id    *traverse_ids;

    traverse_ids = head_socket_id;
    if (traverse_ids == NULL)
    {
        head_socket_id = new_socket_id(sockfd, address);
        traverse_ids = head_socket_id;
    }
    else
    {
        traverse_ids = add_socket_id(head_socket_id, sockfd, address);
        traverse_ids = head_socket_id;
    }
    return (head_socket_id);
}
