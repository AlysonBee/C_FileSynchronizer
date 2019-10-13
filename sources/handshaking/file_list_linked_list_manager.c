

#include "../../includes/file_sync.h"

/* 
** Creates a new file list node.
** @param: filename: The name of the file being saved.
** @param: filesize: The size of the file being saved.
** @param: timestamp: The last edited time of the file.
** @param: file_content: The contents of the file being saved.
*/

t_file_list		*new_file_list_node(char *filename,
	uint64_t filesize,
	time_t timestamp,
	unsigned char *file_content)
{
	t_file_list *head;

	head = (t_file_list *)malloc(sizeof(t_file_list));
	head->filename = strdup(filename);
	head->filesize = filesize;
	head->timestamp = timestamp;
	head->file_content = (unsigned char *)malloc(sizeof(unsigned char) *
		filesize);
	memcpy(head->file_content, file_content, filesize);
	head->next = NULL;
	return (head);	
}

t_file_list 	*add_file_list_node(t_file_list *head,
	char *filename,
	uint64_t filesize,
	time_t timestamp,
	unsigned char *file_content)
{
	t_file_list	*traverse;

	traverse = head;
	while (traverse->next)
		traverse = traverse->next;
	traverse->next = (t_file_list *)malloc(sizeof(t_file_list));
	traverse->next->filename = strdup(filename);
	traverse->next->filesize = filesize;
	traverse->next->timestamp = timestamp;
	traverse->next->file_content = (unsigned char *)malloc(sizeof(unsigned char) *
		filesize);
	memcpy(traverse->next->file_content, file_content, filesize);
	traverse->next->next = NULL;
	return (traverse);
}

t_file_list		*create_and_add_file_list_node(t_file_list *head,
	char *filename,
	uint64_t filesize,
	time_t timestamp,
	unsigned char *file_content)
{
	t_file_list	*traverse;

	traverse = head;
	if (head == NULL)
	{
		head = new_file_list_node(filename, filesize, timestamp, file_content);
	}
	else
	{
		traverse = add_file_list_node(head, filename, filesize, timestamp,
			file_content);
		traverse = head;
	}
	return (head);
}

