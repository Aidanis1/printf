#include "main.h"


/**
 * handle_write_char - Printing  string
 * @c: the types of the characters
 * @buffer: an array of buffer for printing
 * @flags:  Calculaings active flags.
 * @width:  width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */

int handle_write_char(char c, char buffer[],int flags, int width, int precision, int size)
{
	int pad = ' ';
	int j = 0;

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
	{
		pad = '0';
	}

	buffer[j++] = c;
	buffer[j] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (j = 0; j < width - 1; j++)
		{
			buffer[BUFF_SIZE - j - 2] = pad;
		}
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - j - 1], width - 1) + write(1, &buffer[0], 1));
		}
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Printing  string
 * @is_negative: arguments list
 * @ind: character types.
 * @buffer: array of buffer for printing
 * @flags:  Calculating active flags
 * @width: take width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1;
	char pad = ' ', ext_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		pad = '0';
	}
	if (is_negative)
	{
		ext_ch = '-';
	}
	else if (flags & F_PLUS)
	{
		ext_ch = '+';
	}
	else if (flags & F_SPACE)
	{
		ext_ch = ' ';
	}
	
	return (write_num(ind, buffer, flags, width, precision,len, pad, ext_ch));
}

/**
 * write_num - wrting nums with buffer
 * @ind: index of the num in buffer
 * @buffer: the Buffer
 * @flags: is Flags
 * @width: get width
 * @prec: Precision specifier
 * @length: Num length
 * @padd: Pading character
 * @extra_c: Extra character
 *
 * Return: Number of printed characters.
 */

int write_num(int ind, char buffer[],int flags, int width, int prec,int length, char padd, char extra_c)
{
	int pad_beg = 1, j;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
	{
		return (0);
	}
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
	{
		buffer[ind] = padd = ' ';
	}
	if (prec > 0 && prec < length)
	{
		padd = ' ';
	}
	while (prec > length)
	{
		buffer[--ind] = '0', length++;
	}
	if (extra_c != 0)
	{
		length++;
	}
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
		{
			buffer[j] = padd;
		}
		buffer[j] = '\0';
	if (flags & F_MINUS && padd == ' ')
	{
		if (extra_c)
		{
			buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--pad_beg] = extra_c;
			return (write(1, &buffer[pad_beg], j - pad_beg) + write(1, &buffer[ind], length - (1 - pad_beg)));
		}
	}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
	
}

/**
 * write_unsgnd - Writing  unsigned num
 * @is_negative: negative number indicator
 * @ind: Index whre the num began
 * @buffer: characters array
 * @flags: Flags determiner
 * @width: Width determiner
 * @precision: Precision determiner
 * @size: Size determiner
 *
 * Return: Number of written characters.
 */

int write_unsgnd(int is_negative, int ind, char buffer[], int flags, int width, int precision, int size)
{
	int len = BUFF_SIZE - ind - 1, j = 0;
	char pad = ' ';
	
	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < len)
		pad = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		pad = '0';

	if (width > len)
	{
		for (j = 0; j < width - len; j++)
			buffer[j] = pad;

		buffer[j] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], len) + write(1, &buffer[0], j));

		}
		else
		{
			return (write(1, &buffer[0], j) + write(1, &buffer[ind], len));
		}
	}
	return (write(1, &buffer[ind], len));
}

/**
 * write_pointer - Writing  address of memory
 * @buffer: characters array
 * @ind: Index where the number start in buffer
 * @length: num length
 * @width: determins the width
 * @flags: Flags determiner
 * @padd: Character represents  padding
 * @extra_c: Character that represents extra character
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length, int width, int flags, char padd, char extra_c, int padd_start)
{
	int x;

	if (width > length)
	{
		for (x = 3; x < width - length + 3; x++)
			buffer[x] = padd;
		buffer[x] = '\0';

		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], x - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], x - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], x - padd_start) + write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
