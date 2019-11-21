

#include "../includes/file_sync.h"

bool             user_access_or_node(
        int sockfd,
        int client_type,
        int share_or_sync)
{
    printf("share or sync %d\n", share_or_sync);
    unsigned char       buffer[4096];
    printf("User_access\n");
    bzero(buffer, 4096);
    if (client_type == SERVER)
    {
        printf("receiving ?\n");
        recv(sockfd, buffer, 4096, 0);
        printf("Buffer is %s\n", buffer);
        if (strcmp((const char *)buffer, USER) == 0) // Replace with an encrypted string checker.
            return (false);
        else
            printf("HANDLING API ruling (SERVER)\n");
    }
    else
    {
        printf("share or sync %d / USERTYPE is %d\n", share_or_sync, USERTYPE);
        if (share_or_sync == USERTYPE)
        {
            send(sockfd, USER, 4, 0);
            return (false);
        }
        else
        {
            send(sockfd, API, 3, 0);
            printf("HANDLING API ruling (CLIENT)\n");
        }
    }
    printf("Exiting...\n");
    return (true);
}
