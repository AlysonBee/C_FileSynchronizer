# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>
#define HASH_SIZE 4096


typedef struct s_lst {
    char    *key;
    void    *value;
    void    *next;
}               t_lst;


t_lst *HASH[HASH_SIZE];


t_lst	*lstnew(char const *key, char const *value) {
	t_lst	*tmp;

	tmp = (t_lst *)malloc(sizeof(t_lst));
	if (tmp)
	{
        size_t content_size = sizeof(char) * strlen(value) + 1;
        tmp->value = (void *)malloc(content_size);
        memcpy(tmp->value, value, content_size);

        size_t key_size = sizeof(char) * strlen(key) + 1;
        tmp->key = (char *)malloc(key_size);
        memcpy(tmp->key, key, key_size);

		tmp->next = NULL;
	}
	return (tmp);
}

void	lstadd(t_lst *lst, t_lst *new) {
    t_lst *tmp = lst;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = new;
}


int algo(char *key) {
    unsigned long hash = HASH_SIZE;
    int c;

    int i = 0;
    while (key[i]) {
        c = key[i];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        i++;
    }
    hash %= HASH_SIZE;
    return hash;
}

char *get(char *key) {
    t_lst *tmp = HASH[algo(key)];
    while (tmp) {
        if (strcmp(tmp->key, key) == 0) {
            return tmp->value;
        }
        tmp = tmp->next;
    }
    return NULL;
}

int set(char *key, char *value) {
    int i = algo(key);
    // Is there NO collision?
    if (!HASH[i]) {
        HASH[i] = lstnew(key, value);;
        return i;
    }
    // If theres no collision create an element here
    t_lst *tmp;
    
    // Is the key already set?
    tmp = HASH[i];
    while (tmp) {
        //if ((char *)tmp->value == key) 
        if (strcmp((char *)tmp->key, key) == 0)
        {
            tmp->value = strdup(value);
            return i;
        }
        tmp = tmp->next;
    }
    // If its not set add it to the list
    tmp = lstnew(key, value);
    lstadd(HASH[i], tmp);
    return i;
}

