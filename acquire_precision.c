#include "main.h"

/**
 * acquire_precision - Calculates the precision for printing
 * @format: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * @argslist: List of arguments
 *
 * Return: valuePrecision.
 */
int acquire_precision(const char *format, int *counter, va_list argslist)
{
	int currCounter = *counter + 1;
	int valuePrecision = -1;

	if (format[currCounter] != '.')
		return (valuePrecision);
	valuePrecision = 0;
	for (currCounter += 1; format[currCounter] != '\0'; currCounter++)
	{
		if (is_digit(format[currCounter]))
		{
			valuePrecision *= 10;
			valuePrecision += format[currCounter] - '0';
		}
		else if (format[currCounter] == '*')
		{
			currCounter++;
			valuePrecision = va_arg(argslist, int);
			break;
		}
		else
		{
			break;
		}
	}
	*counter = currCounter - 1;
	return (valuePrecision);
}
