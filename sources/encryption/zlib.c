
#include <stdio.h>
#include <string.h>  // for strlen
#include <assert.h>
#include "zlib.h"

int buffer_compress(char *src, char *dest, size_t dest_size) {
    int ret;
    z_stream defstream;

    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;

    defstream.avail_in = (uInt)strlen(src)+1; // size of input, string + terminator
    defstream.next_in = (Bytef *)src; // input char array
    defstream.avail_out = (uInt)dest_size; // size of output
    defstream.next_out = (Bytef *)dest; // output char array
    
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    ret = deflateEnd(&defstream);
    
    // This is one way of getting the size of the output
    printf("Compressed size is: %lu\n", strlen(dest));
    printf("Compressed string is: %s\n", dest);
    return ret == Z_OK;
}

int buffer_decompress(char *src, char *dest, size_t dest_size) {
    int ret;
    z_stream infstream;

    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;

    infstream.avail_in = (uInt)strlen(src) + 1; // size of input
    infstream.next_in = (Bytef *)src; // input char array
    infstream.avail_out = (uInt)dest_size; // size of output
    infstream.next_out = (Bytef *)dest; // output char array
    
    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    ret = inflateEnd(&infstream);
    
    printf("Uncompressed size is: %lu\n", strlen(dest));
    printf("Uncompressed string is: %s\n", dest);
    return ret == Z_OK;
}

int main(int argc, char* argv[])
{   
    char *original = argv[1]; 
    char com_str[1500];
    char dec_str[1500];
    printf("Attempting to compress string: %s\n", original);
    buffer_compress(original, com_str, 1500);
    buffer_decompress(com_str, dec_str, 1500);
    // make sure uncompressed is exactly equal to original.
    // assert(strcmp(original, dec_str) == 0);

    return 0;
}
