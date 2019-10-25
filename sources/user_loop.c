


#include "../includes/file_sync.h"
#include <pthread.h>


static void         monitoring(int parent_socket, int accept_socket)
{
    int socket_checker;

 
    while (true)
    {
        socket_checker = socket_monitoring(parent_socket, accept_socket);

        if (socket_checker == parent_socket)
        {
            printf("Connector is saving their work\n");
            daemon_recv_process(parent_socket);
        }
   }
}
// DEBUG
int         test_flag(void)
{
    int fd = open(".test_client.txt", O_RDONLY);
    char buffer[2];
    bzero(buffer, 2);
    read(fd, buffer, 2);
    int number = atoi(buffer);
    printf("number is %d\n", number);
    if (number == 1)
    {
        printf("4243");
        return (4243);
    }
    else
    {
        printf("address 4246\n");
        return (4246);
    }
}
// END DEBUG

static void  *make_daemon_socket(void *vargs)
{
    int                 sockfd;
    struct sockaddr_in  socket_address;
    int                 accept_socket;
    int                 parent_socket;

    parent_socket = *((int *)vargs);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error making daemon listening process\n");
        exit(1);
    }
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    //socket_address.sin_port = htons(4243);
    socket_address.sin_port = htons(test_flag());
    if (bind(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0)
    {
        perror("perror bind\n");
    }
    if (listen(sockfd, 5) < 0)
    {
        perror("linsten error\n");
    }
    accept_socket = accept_loop(&sockfd, socket_address);

    monitoring(parent_socket, accept_socket);
    return (NULL);
}

void    *connect_daemon(void *vargs)
{
    int                 sockfd;
    struct sockaddr_in  socket_address;
    int parent_socket = *((int *)vargs);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error initializing daemon.\n");
        exit(1);
    }
    int enable = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    {
        perror("setsockopt");
    } 
    memset(&socket_address, '\0', sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    //socket_address.sin_port = htons(4243);
    socket_address.sin_port = htons(test_flag());
    printf("port is %d\n", socket_address.sin_port);
    sleep(2);
    if (connect(sockfd, (struct sockaddr *)&socket_address, sizeof(socket_address)) < 0)
    {
        perror("connect\n");
    }

    daemon_process(parent_socket);
    return (NULL);
}

void       user_loop(int sockfd, struct sockaddr_in socket_address)
{
    pthread_t    thread_id;
    int          *thread_socket; 
   
    thread_socket = malloc(sizeof(*thread_socket));
    // Daemon 
    *thread_socket = sockfd;
    pthread_create(&thread_id, NULL, make_daemon_socket, thread_socket);
    pthread_create(&thread_id, NULL, connect_daemon, thread_socket);
    pthread_join(thread_id, NULL); 
    printf("daemon connected\n");
}
