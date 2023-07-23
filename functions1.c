#include "main.h"

/* PRINTING UNSIGNED NUMBER */

/**
 * print_unsigned - This function Prints an unsigned number
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
int print_unsigned(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 10) + '0';
		number /= 10;
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/* PRINTING UNSIGNED NUMBER IN OCTAL */

/**
 * print_octal - This function Prints an unsigned number in octal notation
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
int print_octal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{

	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & F_HASH && init_number != 0)
		buffer[x--] = '0';

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}

/* PRINTING UNSIGNED NUMBER IN HEXADECIMAL */

/**
 * print_hexadecimal - Prints an unsigned number in hex.d notation
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
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/* PRINTING UNSIGNED NUMBER IN UPPER HEXADECIMAL */

/**
 * print_hexa_upper - Prints an unsigned number in upper hex.d notation
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
int print_hexa_upper(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/* PRINTING HEXX NUM IN LOWER OR UPPER */

/**
 * print_hexa - This function Prints a hex.d number in lower or upper
 *
 * @map_to: Array of values to map the number to
 * @flag_ch: Calculates active flags
 * @precision: Precision specification.
 * @width: Width.
 * @types: List of arguments.
 * @size: Size specifier.
 * @buffer: Buffer array to handle the print.
 * @flags: Calculates active flags.
 *
 * Return: Number of characters printed.
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int x = BUFF_SIZE - 2;
	unsigned long int number = va_arg(types, unsigned long int);
	unsigned long int init_number = number;

	UNUSED(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[x--] = map_to[number % 16];
		number /= 16;
	}

	if (flags & F_HASH && init_number != 0)
	{
		buffer[x--] = flag_ch;
		buffer[x--] = '0';
	}

	x++;

	return (write_unsgnd(0, x, buffer, flags, width, precision, size));
}
