

#include "../../includes/file_sync.h"

/* payload structure : req/app_name/request_body
 */

typedef struct api_request {
    int sockfd_to_respond_to;
    char *request;
    char *app_name;
}   t_api;

static char     *extract_api_name(unsigned char *buffer)
{
    char    **segments;
    char    *api_name;

    segments = split((char *)buffer, ':');
    api_name = strdup(segments[1]);
    free2d(segments);
    return (api_name);
}

unsigned char   *unpack_request_body(unsigned char *buffer, int api_socket,
        int response_socket)
{
    t_api   *api_body;
    char    **segments;
    char    *api_response;
    size_t  response_size;

    printf("again\n");
    segments = split((char *)buffer, ':');
    api_body = (t_api *)malloc(sizeof(t_api));
    api_body->request = strdup(segments[2]);
    api_body->app_name = strdup(segments[1]);
    printf("sending sting %s\n", api_body->request);
    send(api_socket, api_body->request, strlen(api_body->request) + 1, 0);
    
    // Content for Hello World buffer.
    char buf[4096];
    bzero(buf, 4096);
    recv(api_socket, buf, 4096, 0);

    send(response_socket, buf, 4096, 0);
    free(api_body->request);
    free(api_body->app_name);
    free(api_body);
    close(response_socket);
}

bool    check_api_request(socket_t *socket_list, unsigned char *buffer,
        int socket_number)
{
    socket_t    *current;
    char        *api_name;

    api_name = extract_api_name(buffer);
    current = socket_list;
    while (current)
    {
        printf("api name : %s\n", api_name);
        if (current->app_name && strcmp(current->app_name, api_name ) == 0)
        {
            printf("First\n");
            unpack_request_body(buffer, current->sockfd, socket_number);
            free(api_name);
            return (true);
        }
        current = current->next;
    }
    printf("Exiting\n");
    return (false);
}















