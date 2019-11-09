
#include "../includes/file_sync.h"


struct sockaddr_in      create_client_side_listening_socket(int *listen_sockfd)
{
    struct sockaddr_in  socket_address;

    *listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (*listen_sockfd < 0)
    {
        perror("Error creating socket\n");
    }
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(8942);

    if (bind(*listen_sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0)
    {
        perror("Error binding\n");
    }
    
    listen(*listen_sockfd, 5);

    return (socket_address);
}


static int32_t  set_file_descriptors(fd_set *fd_list, t_id *file_list, int sockfd)
{
    int32_t     counter;
    int32_t     max_file_descriptor;
    t_id        *traverse_id;
     
    counter = 0;
    traverse_id = file_list;
    max_file_descriptor = sockfd;
    FD_SET(sockfd, fd_list);
    while (traverse_id)
    {
        FD_SET(traverse_id->sockfd, fd_list);
        if (traverse_id->sockfd > max_file_descriptor)
            max_file_descriptor = traverse_id->sockfd;
        traverse_id = traverse_id->next;
    }
    return (max_file_descriptor);
}

static void     reset_file_descriptor_list(fd_set *fd_list, int sockfd)
{
    FD_ZERO(fd_list);
    FD_SET(sockfd, fd_list);
}

void            sync_loop(int sockfd, int client_type, struct sockaddr_in socket_address)
{
    int32_t max_file_descriptor;
    int32_t trigger;
    
    fd_set  file_descriptor_list;
    t_id    *file_list;

    file_list = NULL;
    max_file_descriptor = sockfd;

    // if user is client, a listening (server) socket has to be created
    // for select() polling.
    if (client_type == CLIENT)
    {
        int temporary_socket;
        socket_address = create_client_side_listening_socket(&temporary_socket);
       
        file_list = socket_id_list_manager(file_list, temporary_socket, "NULL");
       
        sockfd = temporary_socket;
        max_file_descriptor = temporary_socket;
    }
    else
    {
        file_list = socket_id_list_manager(file_list, sockfd, "NULL");
        max_file_descriptor = sockfd;
    }
    
    
    printf("entering 42\n");
    while (42)
    {
        // Zero out file descriptor list and set sockfd to list.
        reset_file_descriptor_list(&file_descriptor_list, sockfd);

        // Set all file descriptors in list to file_descriptor
        // and set max_file_descriptor value.
        set_file_descriptors(&file_descriptor_list, file_list, sockfd);

        printf("Blocked Trigger\n");
        printf("max fd : %d\n", max_file_descriptor);
        trigger = select(max_file_descriptor + 1,
                        &file_descriptor_list, 
                        NULL, NULL, NULL);
        printf("trigger set : %d\n", trigger);
        if (trigger)
        {
            if (FD_ISSET(sockfd, &file_descriptor_list))
            {
                sync_accept(sockfd, file_list, socket_address);
            }
            else
                printf("Something's happening locally\n");
        }


    }
}











