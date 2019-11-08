
#include "../includes/file_sync.h"



int remove_directory(const char *path)
{
    DIR     *dp;
    struct stat info;
    struct dirent *dir;
    char    **directory_list;
    char    *full_path;

    dp = opendir(path);
    directory_list = NULL;
    if (dp == NULL)
    {
        printf("path is %s\n", path);
        perror("opendir");
        return (-1);
    }
    while ((dir = readdir(dp)))
    {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            continue ;
 
        full_path = generate_path((char*)path, dir->d_name);
        printf("full path %s\n", full_path);
        stat(full_path, &info);

        if (S_ISDIR(info.st_mode))
            directory_list = arraypush(directory_list, full_path);
        else
        {
            printf("\tunlinking : %s\n", full_path);
            remove(full_path);
        }
        free(full_path);
    }
    closedir(dp);

    int     counter = 0;
    if (directory_list)
    {
        while (directory_list[counter])
        {
            remove_directory(directory_list[counter]);
            counter++;
        }
        free2d(directory_list);
    }
    int i = remove(path);
    printf("removal is %d\n", i);
    return (0);
}
/*
int remove_directory(const char *path)
{
   
    
    DIR *d = opendir(path);
   printf("removing directory %s\n", path);
 


   size_t path_len = strlen(path);
   int r = -1;
   
   if (d)
   {
      struct dirent *p;
      r = 0;
      while (!r && (p=readdir(d)))
      {
          int r2 = -1;
          char *buf;
          size_t len;
          
          if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, ".."))
             continue;
          printf("first layer\n");
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);
          if (buf)
          {
             struct stat statbuf;
             if (stat(buf, &statbuf))
             {
                 printf("IS IT A DIRECTORY OR FILE\n");
                if (S_ISDIR(statbuf.st_mode))
                {
                    printf("it's a DIR\n");
                   r2 = remove_directory(buf);
                }
                else
                {
                    printf("IT'S A FILE\n");
                   r2 = unlink(buf);
                }
             }
             free(buf);
          }
          else
              perror("first layer\n");
          r = r2;
      }
      closedir(d);
   }
   else
       perror("DIRECTORY DELETION\n");
   if (!r)
      r = rmdir(path);
   return r;
}*/

void        delete_file_or_directory(char *buffer)
{
    struct stat info;

    stat(buffer, &info);
    if (S_ISDIR(info.st_mode))
        remove_directory(buffer);
    else
        unlink(buffer);
}

