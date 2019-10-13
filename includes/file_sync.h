
#ifndef FILE_SYNC
#define FILE_SYNC

#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "handshake.h"
#include "../alylibc/inc/lib.h"

#define MAGIC_NUMBER_SIZE 5
#define BITSHIFTING_MULTIPLIER 8
#define MAGIC_NUMBER 0xE0D5CD7185
#define SERVER 1
#define CLIENT 2

/* The transmission header is the section of bytes at the very start of a constructed
** bufffer to be sent to the neighboring client.
*/

typedef struct s_transmission_buffer_head {
	int32_t trust_key; 			// The unique "magic number" that denotes a legal payload.
	int32_t total_payload_size;	// The total paylaod size to be received.
	int32_t	number_of_files;		// The number of files contained in the payload.	
}	t_transmission_head;


/* The section that immediately follows the transmission_buffer_head.
** Each file_information block contains relevant data for the file content
** located at the fileoff index from the start of the file.
** To successfully gather every file in the payload, a loop the size of
** file information * the number_of_files from the transmission head
** is done.
*/

typedef struct s_file_information {
	char		*filename;		// The name of the file.		
	uint64_t	filesize;		// The size of this file.
	time_t		timestamp;		// The timestamp in epoch formatted seconds.
	uint64_t	fileoff;		// The offset to the file's contents from the start of the buffer.
}	t_file_info;


/* Structures for handling the construction of a local file list that will be used for
** serializing the data into a transmission buffer.
*/

typedef struct s_file_list {
	char		*filename;		// The filename
	uint64_t	filesize;		// The file size
	time_t		timestamp;		// The file's timestamp.
	unsigned char *file_content;
	struct s_file_list	*next;	
}	t_file_list;


typedef struct s_local_client_file_list {
	uint64_t	total_file_sizes;	// Total size of all the files in local directory.
	t_file_list	*file_list;			// List of all local files and their information (see struct above).		
	int32_t		number_of_files;	// The number of files in t_file_list linked list.
}	t_local_file_list;


typedef struct s_directory {
	char *directory_name;
	struct s_directory *next;
}	t_dir;


/* utils.c */

char	*parse_command_line_flags(int argc, char **argv);
void	print_file_list(t_file_list *head);

/* server.c */

void	server(char **argv);

/* client.c */

void	client(char **argv);
void	DEBUG_BUFFER(unsigned char *buffer_start,
	uint64_t byte_count);
void	print_buffer_number(unsigned char *transmission_buffer);

/* handshake/file_list_linked_list_manager */

t_file_list		*create_and_add_file_list_node(t_file_list *head,
	char *filename,
	uint64_t filesize,
	time_t timestamp,
	unsigned char *file_content);

/* handshake/serialize_transmission_buffer.c */

unsigned char	*serialize_transmission_buffer(t_local_file_list *tramsmission_buffer_template);

/* handshake/handshake.c */

void	handshake(int sockfd, int client_type);
unsigned char	*write_trust_key(void);

/* handshake/number_of_files.c */

int32_t		number_of_files(t_file_list *file_list);

/* handshake/total_of_all_file_sizes.c */

uint64_t	total_of_all_file_sizes(t_file_list *file_list);

/* handshake/gather_all_file_info.c */

t_file_list	 	*gather_all_file_info(void);
t_file_list	 	*all_files_on_this_client(char *current_directory,
	t_file_list *file_list);
time_t			extract_file_timestamp(char *target_file);

/* handshake/deserialize_transmission_buffer.c */

t_file_list		*deserialize_transmission_buffer(unsigned char *received_buffer);
uint64_t		extract_number_from_buffer(unsigned char *receive_buffer);

/* handshaake/send_and_receive_buffer_manager.c */

unsigned char	*send_and_receive_manager(int sockfd, int client_type,
	t_local_file_list *file_list);

/* handshake/directory_linked_list_manager.c */

t_dir			*create_and_add_directory(t_dir *head, char *directory_name);

/* handshake/resolve_file_conflicts.c */

void			resolve_file_conflicts(unsigned char *remote_file_system);

#endif
