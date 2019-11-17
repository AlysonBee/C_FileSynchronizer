

#include "encryption.h"


static void DEBUG_PREPARE_KEY(unsigned char state[])
{
    int i = 0;
    int n = 0;
    while (i < 256)
    {
        n = rand() % 255 + 1;
        state[i] = n;
    }
} 


unsigned char   *decompress_and_decrypt(unsigned char *transmission_buffer,
        uint64_t size)
{
    unsigned char state[256];
    rc4(transmission_buffer, size);
}

unsigned char   *compress_and_encrypt(unsigned char *transmission_buffer,
        uint64_t size)
{
    unsigned char state[256];

    DEBUG_PREPARE_KEY(state);
    rc4(transmission_buffer, size, state);

    return (transmission_buffer);
}


















