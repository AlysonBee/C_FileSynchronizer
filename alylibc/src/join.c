
#include "lib.h"

char	*join(char *s1, char *s2)
{
	char	*new;
	size_t	size;

	size = strlen(s1) + strlen(s2);
	new = (char*)malloc(sizeof(char) * size + 1);
	strcpy(new, s1);
	strcat(new, s2);
	new[size] = '\0';
	return (new);
}
