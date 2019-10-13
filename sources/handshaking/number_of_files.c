


#include "../../includes/file_sync.h"

int32_t		number_of_files(t_file_list *file_list)
{
	t_file_list	*traverse;
	int32_t		counter;
	
	counter = 0;
	traverse = file_list;
	while (traverse)
	{
		counter++;
		traverse = traverse->next;
	}
	return (counter);
}
