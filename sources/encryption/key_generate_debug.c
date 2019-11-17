
#include <stdio.h>
#include <stdlib.h>

static void DEBUG_PREPARE_KEY(unsigned char state[])
{
    int i = 0;
    int n = 0;
    while (i < 256)
    {
        n = rand() % 255 + 1;
        printf("n : %d\n", n);
        state[i] = n;
        i++;
    }
}

int main(void) 
{
    unsigned char buffer[256];
    DEBUG_PREPARE_KEY(buffer);
    int i = 0;
    while (i < 256)
    {
        printf("%x", buffer[i]);
        i++;
    }
}
