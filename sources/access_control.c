

#include "../includes/file_sync.h"

bool     application_joining_network(unsigned char buffer [])
{
    printf("buffer app join is %s\n", buffer);
    if (strncmp((char *)&buffer[5], "APPLICATION_NAME", 16) == 0)
        return (true);
    return (false);
}

bool             user_access_or_node(
        int sockfd,
        int client_type,
        int share_or_sync,
        unsigned char buffer [])
{
    bzero(buffer, 4096);
    if (client_type == SERVER)
    {
        recv(sockfd, buffer, 4096, 0);
        printf("buffer is %s\n", buffer);
        if (strcmp((const char *)buffer, USER) == 0)
            return (false);
        else if (strncmp((char *)&buffer[5], "APPLICATION_NAME", 16) == 0)
            return (false);
        else if (strncmp((const char *)buffer, "req", 3) == 0)
            return (false);

            printf("HANDLING API ruling (SERVER)\n");
    }
    else
    {
        if (share_or_sync == USERTYPE)
        {
            send(sockfd, USER, 4, 0);
            return (false);
        }
        else
        {
            send(sockfd, API, 3, 0);
        }
    }
    printf("Exiting...\n");
    return (true);
}
