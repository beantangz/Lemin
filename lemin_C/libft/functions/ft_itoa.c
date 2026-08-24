#include "libft.h"

static int len_int(long number)
{
	int count;

	count = 0;
	if (number < 0)
	{
		number = -number;
		count++;
	}
	while (number > 9)
	{
		number /= 10;
		count++;
	}
	return (count + 1);
}

char *ft_itoa(int number)
{
	char *result;
	long value;
	int length;

	value = number;
	length = len_int(value);
	result = malloc((size_t)length + 1);
	if (result == NULL)
		return (NULL);
	result[length] = '\0';
	length--;
	if (value == 0)
		result[0] = '0';
	if (value < 0)
	{
		result[0] = '-';
		value = -value;
	}
	while (value > 0)
	{
		result[length] = (char)((value % 10) + '0');
		value /= 10;
		length--;
	}
	return (result);
}
