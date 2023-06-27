#include "main.h"

/**
 * get_size - Calculating  size for casting an argument
 * @format: Formatted string for  printing  arguments
 * @j:argument list to print
 *
 * Return: Precision.
 */
int get_size(const char *format, int *j)
{
	int current_j = *j + 1;
	int size = 0;

	if (format[current_j] == 'l')
	{
		size = S_LONG;
	}
	else if (format[current_j] == 'h')
	{
		size = S_SHORT;
	}
	if (size == 0)
	{
		*j = current_j - 1;
	}
	else
	{
		*j = current_j;
	}
	return (size);
}
