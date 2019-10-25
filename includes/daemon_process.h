
#ifndef DAEMON_PROCESS_
#define DAEMON_PROCESS_

// Authored by George Sferopoulos
//
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define HASH_SIZE 9182

char		*uitoa(unsigned long long value);

typedef struct s_lst {
    char    *key;
    void    *value;
    void    *next;
}               t_lst;

unsigned long long  local_shasum(char *file_path);
int set(char *key, char *value);
char *get(char *key);
int algo(char *key);
void	lstadd(t_lst *lst, t_lst *new);
t_lst	*lstnew(char const *key, char const *value);

#endif 
