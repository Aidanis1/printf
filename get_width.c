#include "main.h"

/**
 * get_width - Calculating the width for printing
 * @format: Formatted string for printing  arguments.
 * @j: argument list to print
 * @list: argument list
 *
 * Return: width.
 */
int get_width(const char *format, int *j, va_list list)
{
	int current_j;
	int wid = 0;

	for (current_j = *j + 1; format[current_j] != '\0'; current_j++)
	{
		if (is_digit(format[current_j]))
		{
			wid *= 10;
			wid += format[current_j] - '0'
		}
		else if (format[current_j] == '*')
		{
			current_j++;
			wid = va_arg(list, int);
			break;
		}
		else
		{
			break;
		}
	}
	*j = current_j - 1;
	return (wid);
}
