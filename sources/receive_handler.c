
#include "../includes/file_sync.h"

int remove_directory(const char *path)
{
   DIR *d = opendir(path);
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
          len = path_len + strlen(p->d_name) + 2; 
          buf = malloc(len);
          if (buf)
          {
             struct stat statbuf;
             if (!stat(buf, &statbuf))
             {
                if (S_ISDIR(statbuf.st_mode))
                   r2 = remove_directory(buf);
                else
                   r2 = unlink(buf);
             }
             free(buf);
          }
          r = r2;
      }
      closedir(d);
   }
   if (!r)
      r = rmdir(path);
   return r;
}

void        delete_file_or_directory(char *buffer)
{
    struct stat info;

    stat(buffer, &info);
    if (S_ISDIR(info.st_mode))
        remove_directory(buffer);
    else
        unlink(buffer);
}

void        create_directory(char *buffer)
{
    mkdir(buffer, 0755);
}

void        receive_handler(unsigned char *buffer)
{
    char    **unpack;

    unpack = split((char *)buffer, ':');
    if (strcmp("dir", unpack[0]) == 0)
        mkdir(unpack[1], 0755);
    else if (strcmp("del", unpack[0]) == 0)
        delete_file_or_directory(unpack[1]);
}
