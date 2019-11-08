

#include "../includes/file_sync.h"
#include "../includes/daemon_process.h"
#include <errno.h>

t_lst       *HASH[HASH_SIZE];
void        create_directory_list();
char        root_directory[4096];
#define DEL_MESSAGE_SIZE 3


t_dir       *directory_list(char *, t_dir *);


t_dir      *directory_list(char *here, t_dir *traverse)
{
    struct stat         info;
    struct dirent       *dir;
    DIR                 *dp;
    char                *pathname;
    t_dir               *local_directory;
    char                **directories = NULL;

    local_directory = NULL;
    dp = opendir(here);
    if (dp == NULL) {perror("DIRECTORY "); return NULL;};
    while ((dir = readdir(dp)))
    {
        if (dir->d_name[0] == '.')
            continue ;
        
        pathname = generate_path(
            here, dir->d_name
        );

        stat(pathname, &info);
        if (S_ISDIR(info.st_mode))
            directories = arraypush(directories, pathname);
        else
        {
            traverse = create_and_add_directory(
                traverse, pathname
            );
        }
    }
    closedir(dp);
   

    int i = 0;
    if (directories)
    {
        while (directories[i])
        {
            directory_list(directories[i], traverse);
            i++;
        }
        free2d(directories);
    }
    return (traverse);
}

void        create_directory_list(void)
{
    t_dir   *list = NULL;
    t_dir   *travel;
    char    *value;

    list = directory_list(".", list);
    travel = list;
    while (travel)
    {
        value = uitoa(local_shasum(travel->directory_name));
        set(travel->directory_name, value);
        travel = travel->next;
    }
    
}

void        print_everything_here(void)
{
    DIR *dp;
    struct dirent *directory;
    char *fullpath;

    dp = opendir(".");
    while ((directory = readdir(dp)))
    {
        if (directory->d_name[0] == '.')
            continue;
        fullpath = generate_path(
            ".", directory->d_name
        );
        char *value = get(fullpath);
    
        if (value)
           printf("key %s : value is %s\n", fullpath, value);

    }
    closedir(dp);
}

void        send_buffer_size(uint64_t file_size, int sockfd)
{
    unsigned char       *buffer;

    buffer = (unsigned char*)itoa(file_size);
    send(sockfd, buffer, strlen((char *)buffer) + 1, 0);
    free(buffer);
}

void        send_updated_file(t_file_list *node_to_send, int sockfd)
{
    unsigned char       *transmission_buffer;
	uint64_t			file_size;
	int32_t				files_count;
	t_local_file_list	*transmission_buffer_template;

	unsigned char	    *buffer_to_send;
	int64_t			    local_buffer_size;

    files_count = number_of_files(node_to_send);
	file_size = total_of_all_file_sizes(node_to_send);

    transmission_buffer_template = (t_local_file_list *)malloc(
		sizeof(t_local_file_list));

    transmission_buffer_template->total_file_sizes = file_size;
	transmission_buffer_template->file_list = node_to_send;
	transmission_buffer_template->number_of_files = files_count;

    transmission_buffer = serialize_transmission_buffer(
        transmission_buffer_template
    );

	buffer_to_send = serialize_transmission_buffer(transmission_buffer_template);
	local_buffer_size = total_file_size(buffer_to_send);
    print_file_list(node_to_send);
    send_buffer_size(local_buffer_size, sockfd);
  //  DEBUG_BUFFER(buffer_to_send, local_buffer_size);
    sleep(1);
    controlled_send(sockfd, buffer_to_send, local_buffer_size);
   // send(sockfd, buffer_to_send, local_buffer_size, 0);
    free(buffer_to_send);
    free(transmission_buffer_template);
    sleep(3);
}

bool        check_last_word(char *line, char *last_word)
{
    char     **segments;
    int      index;

    if (strchr(line, '/'))
    {
        segments = split(line, '/');
        index = arraylen(segments);
        if (strncmp(segments[index - 1], last_word, 4) == 0)
        {
            free2d(segments);
            return (true);
        }
    }
    else
    {
        if (strncmp(line, last_word, 4) == 0)
            return (true);
    }
    return (false);
}

char        *serialize_deletion(char *file_to_check)
{
    unsigned char *buffer;

    buffer = (unsigned char *)malloc(sizeof(unsigned char) *
        strlen((char *)file_to_check) + 1 + DEL_MESSAGE_SIZE);
    memcpy(buffer, "del:", 4);
    memcpy(&buffer[4], file_to_check, strlen((char *)file_to_check) + 1);
    printf("buffer is >>  %s\n", buffer);
    return ((char *)buffer);
} 



bool         skipping_hidden_files(char *content)
{
    char    **file_segments;
    int32_t counter;
    bool    flag;

    flag = false;
    file_segments = split(content, '/');
    if (!file_segments)
        return false;
    counter = 0;
    while (file_segments[counter])
        counter++;
    counter--;
    if (file_segments[counter][0] == '.')
       flag = true;
    free2d(file_segments);
    return (flag);
}

char        *checking_access(char *content, size_t root_length)
{
    char        *file_to_check;
    char        *deletion;

    file_to_check = &content[root_length + 1];
    if (skipping_hidden_files(file_to_check))
        return (NULL);

    // if the file is a file and NOT a folder and it exists
    if (access(file_to_check, F_OK) != -1 && !check_folder_path_exists(file_to_check))
    {
        return (strdup(file_to_check));
    }

    // if the file is a folder.
    if (check_folder_path_exists(file_to_check))
    {
        return (NULL);
    }
    // else it's being deleted.
    deletion = serialize_deletion(file_to_check);
    if (deletion)
    {
        return (deletion);
    }
    return (NULL);
}

char        *vim_support(char **directory_list, int root_length)
{
    char    *edited_file;
    int32_t counter;

    counter = 0;
    edited_file = NULL;
    while (directory_list[counter])
    {
        if (check_last_word(&directory_list[counter][root_length + 1], "4913") == true)
        {
            edited_file = strdup(&directory_list[counter + 1][root_length + 1]);
            break ;
        }
        counter++;
    }
    return (edited_file);
}

char        *file_list_string(char *current_string, char *to_add, char *delim)
{
    char    *newstring;
    char    *addition;

    newstring = strdup(current_string);
    addition = join(newstring, delim);
    free(newstring);
    newstring = join(addition, to_add);
    free(addition);
    return (newstring);
}

char        *basic_file_creation(char **directory_list, int root_length)
{
    int32_t i;
    char    *edited_file;
    char    *file_list;
    char    *delim;
    
    file_list = (char *)malloc(sizeof(char));
    edited_file = NULL;
    i = 0;
    while (directory_list[i])
    {
        edited_file = checking_access(directory_list[i], root_length);

        if (edited_file)
        {
            delim = strdup(",");
            file_list = file_list_string(edited_file, file_list, delim);
            free(edited_file);
            free(delim);
        }
        i++;
    }
    return (file_list);
}

char        *check_for_changed_state(char *content)
{
    char    **directory_list;
    int     counter;
    char    *edited_file;
    size_t  root_length;

    edited_file = NULL;
    root_length = strlen(root_directory);
    directory_list = split(content, '\n');


    printf("VIM SUPPORT\n");
    edited_file = vim_support(directory_list, root_length);
    if (edited_file)
        return (edited_file);


    printf("BASIC FILE SUPPORT\n");
    edited_file = basic_file_creation(directory_list, root_length);
    if (edited_file)
        return (edited_file);


    return (edited_file);
}

char        *fswatch_systemcall(void)
{
    int     fd;
    char            *buffer;
    struct stat     info;
    char            *changed_file;
    extern char     *g_coordinate;

    system("fswatch --one-event -r . > .watchman");
    if (g_coordinate != NULL)
    {
        free(g_coordinate);
        g_coordinate = NULL;
        sleep(1);
        unlink(".watchman");
        return (NULL);
    }
    fd = open(".watchman", O_RDONLY);
    
    fstat(fd, &info);
    buffer = (char *)malloc(sizeof(char) * info.st_size + 1);
    bzero(buffer, info.st_size + 1);
    read(fd, buffer, info.st_size);
    close(fd);
    
    if (check_folder_path_exists(buffer))
    {
        free(buffer);
        return (NULL);
    }
    changed_file = check_for_changed_state(buffer);
    free(buffer);
    if (changed_file == NULL)
        return NULL;
    return (changed_file);
}

void        assign_local_directory(void)
{
    bzero(root_directory, 4096);
    getcwd(root_directory, 4096);
}

t_file_list *send_file(char *filename)
{
    char    **file_list;
    int32_t counter;
    t_file_list *tosend;

    tosend = NULL;
    file_list = NULL;
    counter = 0;
    if (strchr(filename, ','))
    {
        file_list = ft_strsplit(filename, ',');
        while (file_list[counter])
        {
            if (check_folder_path_exists(file_list[counter]))
            {
                counter++;
                continue;
            }
            tosend = create_and_add_file_list_node(
                tosend,
                file_list[counter],
                extract_file_size(file_list[counter]),
                extract_file_timestamp(file_list[counter]),
                extract_file_content(file_list[counter])
           );
           counter++;
        }
        free2d(file_list);
    }
    else
    {
        tosend = new_file_list_node(
            filename,
            extract_file_size(filename),
            extract_file_timestamp(filename),
            extract_file_content(filename)
        );
    }
    return (tosend);
}


char        *handle_deletion(char *file)
{
    char    **file_list;
    char    *file_to_delete;
    int32_t counter;
    char    *delim;

    if (!strchr(file, ','))
        return (file);
    file_list = ft_strsplit(file, ',');
    if (!file_list)
        return (file);
    file_to_delete = (char *)malloc(sizeof(char));
    delim = strdup(",");
    counter = 0;
    while (file_list[counter])
    {
        file_to_delete = file_list_string(file_to_delete, file_list[counter], delim);
        counter++;
    }
    free2d(file_list);
    free(delim);
    free(file);
    file = NULL;
    return (file_to_delete);
}

void        send_deletion_instruction(char *deletion_list, int sockfd)
{
    uint64_t    list_length;

    list_length = strlen(deletion_list);
    send_buffer_size(list_length, sockfd);

    sleep(1);

    controlled_send(sockfd, (unsigned char *)deletion_list, list_length);
    printf("Buffer sent\n");
}

void        daemon_process(int sockfd)
{
    assign_local_directory();
    create_directory_list();
    char    *file;
    extern char *g_coordinate;
    bool    flag;

    flag = false;
    printf("here\n");
    while (true)
    {
        printf("again\n");
        if (flag == true)
        {
            flag = false;
            printf("FLAG STUFF\n");

            sleep(2);
            continue ;
        }
        file = fswatch_systemcall();

        if (file)
        {
           printf("file is ~~~~~~ %s\n", file);
           if (strstr(file, "del:") && g_coordinate == NULL)
           {
               printf("BEFORE HANDLE DELETION\n");
               file = handle_deletion(file);
               printf("ENDING HANDLIND\n"); 
               send_deletion_instruction(file, sockfd);
                //send(sockfd, (unsigned char *)file, strlen((char *)file) + 1, 0);
           }
           else
                send_updated_file(send_file(file), sockfd);
           if (file)
               free(file);
           //free(file);
           flag = true;
        }
    }
}
/*
int main(void)
{
    t_dir *head = NULL;
     daemon_process(42);
    
    return (0);
} */
