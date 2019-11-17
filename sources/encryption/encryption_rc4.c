

#include <stdlib.h>
#include "encryption.h"


static void DEBUG_PREPARE_KEY(unsigned char *keydata, int32_t length, rc4_t *key)
{
    int32_t index1;
    int32_t index2;
    int32_t counter;
    unsigned char *state;

    state = key->state;
    counter = 0;
    while (counter < 256)
    {
        state[counter] = counter;
        counter++;
    }
    index1 = 0;
    index2 = 0;
    counter = 0;
    while (counter < 256)
    {
        index2 = (keydata[index1] + state[counter] + index2) & 255;
        state[counter] ^= state[index2];
        state[index2] ^= state[counter];
        state[counter] ^= state[index2];
        index1 = (index1 + 1) % length;
        counter++;
    }
}


void    rc4(unsigned char *buffer, unsigned char length, 
        unsigned char state[])
{
    int32_t x;
    int32_t y;
    int32_t xor_index;
    int32_t counter;

    x = 0;
    y = 0;
    counter = 0;
    while (counter < length)
    {
        x = (x + 1) & 255;
        y = (state[x] + y) % 255;
        state[x] ^= state[y];
        state[y] ^= state[x];
        state[x] ^= state[y];
        xor_index = (state[y] + state[x]) & 255;
        buffer[counter] ^= state[xor_index];
        counter++;
    }
}

/*
int     main(void)
{
    unsigned char in[4], out[4], out2[4];
    unsigned char user_key[8];
    rc4_t key;
    memset(in, 2, sizeof(in));
   
    memset(user_key, 0, sizeof(user_key));
    DEBUG_PREPARE_KEY(user_key, sizeof(user_key), &key);
    memcpy(out, in, sizeof(in));
    rc4(out, 4, &key);

    memset(user_key, 0, sizeof(user_key));
    DEBUG_PREPARE_KEY(user_key, sizeof(user_key), &key);
    memcpy(out2, out, sizeof(out));
    rc4(out2, 4, &key);

    print_buffer(in, 4);
    print_buffer(out, 4);
    print_buffer(out2, 4);
    
    return (0);
} */
