

#ifndef API_H
#define API_H

#include "../../includes/file_sync.h"
#define SYNC 1
#define NO_SYNC 2

typedef struct  s_api 
{
    uint64_t        trust_key;
    char            *api_key;
    char            *app_name;
    int32_t         request_type;
    unsigned char   *payload;
}              t_api;




#endif
