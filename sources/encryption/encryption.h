
#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include "../includes/file_sync.h"

typedef struct s_key 
{
    unsigned char *state;
}   key_t;

int     buffer_decompress(char *src, char *dest, size_t dest_size);
int     buffer_compress(char *src, char *dest, size_t dest_size);
void    rc4(unsigned char *buffer, unsigned char length,
        unsigned char state[]);


#endif
