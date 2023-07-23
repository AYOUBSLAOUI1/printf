#include "main.h"

/* PRINTING A CHAR */

/**
 * print_char - This function prints a character.
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
int print_char(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/* PRINTING A STRING */

/**
 * print_string - This function prints a string
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
int print_string(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, x;
	char *string = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}

	while (string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], length);
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - length; x > 0; x--)
				write(1, " ", 1);
			write(1, &string[0], length);
			return (width);
		}
	}

	return (write(1, string, length));
}
/* PRINTING A PERCENT SIGN */

/**
 * print_percent - This function prints a percent sign
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
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINTING AN INTEGER */

/**
 * print_int - This function prints an integer
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
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	int is_negative = 0;
	long int b = va_arg(types, long int);
	unsigned long int num;

	b = convert_size_number(b, size);

	if (b == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)b;

	if (b < 0)
	{
		num = (unsigned long int)((-1) * b);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[x--] = (num % 10) + '0';
		num /= 10;
	}

	x++;

	return (write_number(is_negative, x, buffer, flags, width, precision, size));
}

/* PRINTING A BINARY */

/**
 * print_binary - This function prints an unsigned number
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
int print_binary(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	unsigned int k, r, x, sum;
	unsigned int e[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	k = va_arg(types, unsigned int);
	r = 2147483648; /* (2 ^ 31) */
	e[0] = k / r;
	for (x = 1; x < 32; x++)
	{
		r /= 2;
		e[x] = (k / r) % 2;
	}
	for (x = 0, sum = 0, count = 0; x < 32; x++)
	{
		sum += e[x];
		if (sum || x == 31)
		{
			char z = '0' + e[x];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
