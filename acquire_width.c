#include "main.h"

/**
 * acquire_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * @argslist: List of arguments
 *
 * Return: textwidth.
 */
int acquire_width(const char *format, int *counter, va_list argslist)
{
	int currCounter;
	int textwidth = 0;

	for (currCounter = *counter + 1; format[currCounter] != '\0';
				currCounter++)
	{
		if (is_digit(format[currCounter]))
		{
			textwidth *= 10;
			textwidth += format[currCounter] - '0';
		}
		else if (format[currCounter] == '*')
		{
			currCounter++;
			textwidth = va_arg(argslist, int);
			break;
		}
		else
		{
			break;
		}
	}
	*counter = currCounter - 1;
	return (textwidth);
}
