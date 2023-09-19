#include "main.h"

/**
 * acquire_precision - Calculates the precision for printing
 * @inputFmt: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * @argslist: List of arguments
 *
 * Return: Precision.
 */
int acquire_precision(const char *inputFmt, int *counter, va_list argslist)
{
	int currCounter = *counter + 1;
	int valuePrecision = -1;

	if (inputFmt[currCounter] != '.')
		return (valuePrecision);
	valuePrecision = 0;
	for (currCounter += 1; inputFmt[currCounter] != '\0'; currCounter++)
	{
		if (is_digit(inputFmt[currCounter]))
		{
			valuePrecision *= 10;
			valuePrecision += inputFmt[currCounter] - '0';
		}
		else if (inputFmt[currCounter] == '*')
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
