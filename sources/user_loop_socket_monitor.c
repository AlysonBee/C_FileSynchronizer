

#include "../includes/file_sync.h"
#include <sys/time.h>
#include <sys/select.h>

static int     set_file_descriptors(fd_set *socket_pool, int remote_conn_socket,
    daemon_socket)
{
    int     maxfd;

    FD_ZERO(socket_pool);
    FD_SET(remote_conn_socket, socket_pool);
    FD_SET(daemon_socket, socket_pool);
    maxfd = remote_conn_socket > daemon_socket ? remote_conn_socket : daemon_socket;
    return (maxfd);    
}

static int      check_for_active_socket(fd_set socket_pool,
    int remote_conn_socket, int daemon_socket)
{
    if (FD_ISSET(remote_conn_socket, &socket_pool))
        return remote_conn_socket;
    if (FD_ISSET(daemon_socket, &socket_pool))
        return daemon_socket;
    return (-1);
}

int    socket_monitor(int remote_conn_socket, int daemon_socket)
{
    fd_set          socket_pool;
    int             maxfd;
    int             checker;
    struct timeval  seconds;

    maxfd = set_file_descriptors(&socket_pool, remote_conn_socket,
        daemon_socket);

    seconds.tv_sec = 1;
    seconds.tv_usec = 1;
    checker = select(maxfd, &socket_pool, NULL, NULL, NULL);

    return (check_for_active_socket(socket_pool,
                remote_conn_socket, daemon_socket)); 
}




