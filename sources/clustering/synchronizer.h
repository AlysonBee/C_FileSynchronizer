

#ifndef SYNCHRONIZE_H
#define SYNCHRONIZE_H

#include "../../includes/file_sync.h"
#include <poll.h>

typedef struct socket_list 
{
    int                 sockfd;
    struct socket_list  *next;
}   socket_t;


#endif
