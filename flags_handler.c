#include "main.h"

/**
 * flags_handler - This function Calculates active flags
 *
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 *
 * Return: Flags:
 */

int flags_handler(const char *format, int *i)
{
	int k, cur_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (cur_i = *i + 1; format[cur_i] != '\0'; cur_i++)
	{
		for (k = 0; FLAGS_CH[k] != '\0'; k++)
			if (format[cur_i] == FLAGS_CH[k])
			{
				flags |= FLAGS_ARR[k];
				break;
			}
		if (FLAGS_CH[k] == 0)
			break;
	}
	*i = cur_i - 1;
	return (flags);
}
