

#include "../../includes/file_sync.h"

uint64_t	total_of_all_file_sizes(t_file_list *file_list)
{
	t_file_list	*traverse;
	uint64_t	total_payload_size;
	
	traverse = file_list;
	total_payload_size = 0;
	while (traverse)
	{
		total_payload_size += traverse->filesize;
		traverse = traverse->next;
	}
	return (total_payload_size);
}
