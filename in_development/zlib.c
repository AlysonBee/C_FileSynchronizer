/*
#include <stdio.h>
#include <string.h>  // for strlen
#include <assert.h>
#include "zlib.h"

// adapted from: http://stackoverflow.com/questions/7540259/deflate-and-inflate-zlib-h-in-c
int main(int argc, char* argv[])
{   
    // original string len = 36
    char *a = argv[1];

    // placeholder for the compressed (deflated) version of "a" 
    char b[1500];

    // placeholder for the UNcompressed (inflated) version of "b"
    char c[1500];
     

    printf("Uncompressed size is: %lu\n", strlen(a));
    printf("Uncompressed string is: %s\n", a);


    printf("\n----------\n\n");

    // STEP 1.
    // deflate a into b. (that is, compress a into b)
    
    // zlib struct
    z_stream defstream;
    defstream.zalloc = Z_NULL;
    defstream.zfree = Z_NULL;
    defstream.opaque = Z_NULL;
    // setup "a" as the input and "b" as the compressed output
    defstream.avail_in = (uInt)strlen(a)+1; // size of input, string + terminator
    defstream.next_in = (Bytef *)a; // input char array
    defstream.avail_out = (uInt)sizeof(b); // size of output
    defstream.next_out = (Bytef *)b; // output char array
    
    // the actual compression work.
    deflateInit(&defstream, Z_BEST_COMPRESSION);
    deflate(&defstream, Z_FINISH);
    deflateEnd(&defstream);
     
    // This is one way of getting the size of the output
    printf("Compressed size is: %lu\n", strlen(b));
    printf("Compressed string is: %s\n", b);
    

    printf("\n----------\n\n");


    // STEP 2.
    // inflate b into c
    // zlib struct
    z_stream infstream;
    infstream.zalloc = Z_NULL;
    infstream.zfree = Z_NULL;
    infstream.opaque = Z_NULL;
    // setup "b" as the input and "c" as the compressed output
    infstream.avail_in = (uInt)((char*)defstream.next_out - b); // size of input
    infstream.next_in = (Bytef *)b; // input char array
    infstream.avail_out = (uInt)sizeof(c); // size of output
    infstream.next_out = (Bytef *)c; // output char array
     
    // the actual DE-compression work.
    inflateInit(&infstream);
    inflate(&infstream, Z_NO_FLUSH);
    inflateEnd(&infstream);
     
    printf("Uncompressed size is: %lu\n", strlen(c));
    printf("Uncompressed string is: %s\n", c);
    

    // make sure uncompressed is exactly equal to original.
    assert(strcmp(a,c)==0);

    return 0;
}

*/
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
