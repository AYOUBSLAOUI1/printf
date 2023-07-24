#include "main.h"

/* PRINTING A POINTER */

/**
 * print_pointer - Prints the value of a pointer variable
 *
 * @precision: Precision specification.
 * @width: Width.
 * @types: List of arguments.
 * @size: Size specifier.
 * @buffer: Buffer array to handle the print.
 * @flags: Calculates active flags.
 *
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char ex_tra = 0, padd = ' ';
	int in = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long number_addres;
	char map_to[] = "01234abcd";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	number_addres = (unsigned long)addrs;

	while (number_addres > 0)
	{
		buffer[in--] = map_to[number_addres % 16];
		number_addres /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ex_tra = '+', length++;
	else if (flags & F_SPACE)
		ex_tra = ' ', length++;

	in++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, in, length,
				width, flags, padd, ex_tra, padd_start));
}

/* PRINTING A NON PRINTABLE */

/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 *
 * @precision: Precision specification.
 * @width: Width.
 * @types: List of arguments.
 * @size: Size specifier.
 * @buffer: Buffer array to handle the print.
 * @flags: Calculates active flags.
 *
 * Return: Number of characters printed.
 */
int print_non_printable(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int x = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[x] != '\0')
	{
		if (is_printable(str[x]))
			buffer[x + offset] = str[x];
		else
			offset += append_hexa_code(str[x], buffer, x + offset);

		x++;
	}

	buffer[x + offset] = '\0';

	return (write(1, buffer, x + offset));
}

/* PRINTING A REVERSE */

/**
 * print_reverse - Prints reverse string.
 *
 * @precision: Precision specification.
 * @width: Width.
 * @types: List of arguments.
 * @size: Size specifier.
 * @buffer: Buffer array to handle the print.
 * @flags: Calculates active flags.
 *
 * Return: Number of characters printed.
 */

int print_reverse(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char *str;
	int x, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (x = 0; str[x]; x++)
		;

	for (x = x - 1; x >= 0; x--)
	{
		char z = str[x];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* PRINTING A STRING IN ROT13 */

/**
 * print_rot13string - Print a string in rot13.
 *
 * @precision: Precision specification.
 * @width: Width.
 * @types: List of arguments.
 * @size: Size specifier.
 * @buffer: Buffer array to handle the print.
 * @flags: Calculates active flags.
 *
 * Return: Number of characters printed.
 */
int print_rot13string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char y;
	char *str;
	unsigned int x, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvxwyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (x = 0; str[x]; x++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == str[x])
			{
				y = out[k];
				write(1, &y, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			y = str[x];
			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}
