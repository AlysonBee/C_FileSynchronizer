
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>


unsigned long long hash(unsigned char *str) {
    unsigned long long hash = 5381;
    unsigned long long c;

    unsigned long long i = 0;
    while (str[i]) {
        c = str[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        i++;
    }
    return hash;
}


unsigned char *read_file(char *file_path, unsigned long long *size) {
    int fd;
    struct stat info;
    unsigned char *content;

    fd = open(file_path, O_RDONLY);
    if (fd < 0)
        return (NULL);
    fstat(fd, &info);
    *size = info.st_size;
    content = mmap(0, info.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (content == MAP_FAILED)
    {
        return (NULL);
    }
    close(fd);
    return (content);
}

unsigned long long  local_shasum(char *file_path) {

    unsigned char *content;
    unsigned long long     hash_value;
    unsigned long long  filesize;

    content = read_file(file_path, &filesize);
    if (content == NULL)
    {
        return 0;
    }
    hash_value = hash(content);
    munmap(content, filesize);
    return hash_value;
}

/*
int main(int argc, char **argv) {
    if (argc == 1)
        puts("Usage ./a.out <file path>");
    printf("%llu\n", local_shasum(argv[1]));

}*/






