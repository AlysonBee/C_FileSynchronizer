
#include "../../includes/file_sync.h"



socket_t *new_socket(int sockfd, char *ip, bool sync, char *app_name) {
    socket_t *new_sock;

    new_sock = (socket_t *)malloc(sizeof(socket_t));
    new_sock->ip = strdup(ip);
        new_sock->sockfd = sockfd;
    new_sock->sync = sync;
    if (app_name)
        new_sock->app_name = strdup(app_name);
    else
        new_sock->app_name = NULL;
    new_sock->api_socket = false;
    new_sock->next = NULL;
    return (new_sock);
}

socket_t *add_socket(socket_t *head, int sockfd, char *ip, bool sync,
        char *app_name) {
    socket_t *trav;

    trav = head;
    while (trav->next)
        trav = trav->next;
    trav->next = (socket_t *)malloc(sizeof(socket_t));
    trav->next->ip = strdup(ip);
    trav->next->sockfd = sockfd;
    if (app_name)
        trav->next->app_name = strdup(app_name);
    else
        trav->next->app_name = NULL;
    trav->next->api_socket = false;
    trav->next->sync = sync;
    trav->next->next = NULL;
    return (trav);
}


socket_t *push_socket(socket_t *head, int sockfd, char *ip, bool sync,
        char *app_name) {
    socket_t *trav;

    trav = head;
    if (trav == NULL)
        head = new_socket(sockfd, ip, sync, app_name);
    else {
        trav = add_socket(head, sockfd, ip, sync, app_name);
        trav = head;
    }
    return (head);
}

void print_linked_list(socket_t *head) {
    socket_t *current;

    current = head;
    while (current) {
        printf("%d  ", current->sockfd);
        printf("flag : %s\n", current->sync == true ? "True" : "False");
        printf("address : %s\n", current->ip);
        if (current->app_name)
            printf("APP name : %s\n", current->app_name);
        current = current->next;
    }
}
