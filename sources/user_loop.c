


#include "../includes/file_sync.h"
#include <pthread.h>


static void         monitoring(int parent_socket, int accept_socket)
{
    int socket_checker;

    daemon_operation(accept_socket);
    /*
    while (true)
    {
        socket_checker = socket_monitoring(parent_socket, accept_socket);
        if (socket_checker == parent_socket)
            printf("Connector is saving their work\n");
        else
        {
            printf("You saved your work\n");
        } 
   } */
}
// DEBUG
int         test_flag(void)
{
    int fd = open("client_test.txt", O_RDONLY);
    char buffer[2];
    bzero(buffer, 2);
    read(fd, buffer, 2);
    int number = atoi(buffer);
    if (number == 1)
        return (4243);
    else
        return (4244);
    clos(fd);
}
// END DEBUG
static void  *make_daemon_socket(void *vargs)
{
    int                 sockfd;
    struct sockaddr_in  socket_address;
    int                 accept_socket;
    int                 parent_socket;

    parent_socket = *((int *)vargs);
    free(vargs);
    printf("prime_sockt is %d\n", parent_socket);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error making daemon listening process\n");
        exit(1);
    }
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    //socket_address.sin_port = htons(4243);
    socket_address.sin_port = htons(test_flag());
    bind(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address));

    listen(sockfd, 5);

    accept_socket = accept_loop(&sockfd, socket_address);

    socket_monitor(parent_socket, accept_socket);
}

void    *connect_daemon(void *vargs)
{
    int                 sockfd;
    struct sockaddr_in  socket_address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error initializing daemon.\n");
        exit(1);
    }
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //socket_address.sin_port = htons(4243);
    socket_address.sin_port = htons(test_flag());
    sleep(2);
    connect(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address));


}

void       user_loop(int sockfd, struct sockaddr_in socket_address)
{
    pthread_t    thread_id;
    int          *thread_socket; 

    thread_socket = malloc(sizeof(*thread_socket));
    // Daemon 
    *thread_socket = sockfd;
    pthread_create(&thread_id, NULL, make_daemon_socket, thread_socket);
    pthread_create(&thread_id, NULL, connect_daemon, NULL);
        
    printf("daemon connected\n");
}
