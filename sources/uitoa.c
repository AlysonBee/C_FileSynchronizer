
#include <stdlib.h>

unsigned long  u_number_len(unsigned long long value)
{
	unsigned long		size;

	size = 0;
	while (value > 0)
	{
		value /= 10;
		size++;
	}
	return (size);
}

char		*uitoa(unsigned long long value)
{
	unsigned long		size;
	char	*number;

	size = u_number_len(value);
	number = (char*)malloc(sizeof(char) * size + 1);
	number[size--] = '\0';
	while (value > 0)
	{
		number[size] = value % 10 + '0';
		size--;
		value /= 10;
	}
	return (number);
}
