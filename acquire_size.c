#include "main.h"

/**
 * acquire_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 *
 * Return: Size specifier.
 */
int acquire_size(const char *format, int *counter)
{
	int currCounter = *counter + 1;
	int typeSize = 0;

	if (format[currCounter] == 'l')
		typeSize = S_LONG;
	else if (format[currCounter] == 'h')
		typeSize = S_SHORT;

	if (typeSize == 0)
		*counter = currCounter - 1;
	else
		*counter = currCounter;
	return (typeSize);
}
