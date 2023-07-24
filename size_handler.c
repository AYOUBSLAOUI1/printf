#include "main.h"

/**
 * size_handler - This function Calculates the size to cast the argument.
 *
 * @format: Formatted a string.
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int size_handler(const char *format, int *i)
{
	int current_i = *i + 1;
	int size = 0;

	if (format[current_i] == 'l')
		size = S_LONG;
	else if (format[current_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_i - 1;
	else
		*i = current_i;

	return (size);
}
