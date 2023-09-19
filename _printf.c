#include "main.h"

void update_buffer(char tempBuffer[], int *bufferIndex);
/**
 * _printf - Printf function
 * @format: inputFmt.
 * Return: totalcharcount.
 */
int _printf(const char *format, ...)
{

	int counter, totalCharCount = 0, returnedVal = 0;
	int activieFlags, textwidth, valuePrecision, typeSize, bufferIndex = 0;
	va_list argslist;
	char tempBuffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(argslist, format);

	for (counter = 0; format && format[counter] != '\0'; counter++)
	{
		if (format[counter] != '%')
		{
			tempBuffer[bufferIndex++] = format[counter];
			if (bufferIndex == BUFF_SIZE)
				update_buffer(tempBuffer, &bufferIndex);
			totalCharCount++;
		}
		else
		{
			update_buffer(tempBuffer, &bufferIndex);
			activieFlags = acquire_flags(format, &counter);
			textwidth = acquire_width(format, &counter, argslist);
			valuePrecision = acquire_precision(format, &counter, argslist);
			typeSize = acquire_size(format, &counter);
			++counter;
			returnedVal = handle_print(format, &counter, argslist,
				tempBuffer, activieFlags, textwidth, valuePrecision, typeSize);
			if (returnedVal == -1)
				return (-1);
			totalCharCount += returnedVal;
		}
	}

	update_buffer(tempBuffer, &bufferIndex);

	va_end(argslist);

	return (totalCharCount);
}

/**
 * update_buffer - Prints the contents of the buffer if it exist
 * @tempBuffer: Array of chars
 * @bufferIndex: Index at which to add next char, represents the length.
 */
void update_buffer(char tempBuffer[], int *bufferIndex)
{
	if (*bufferIndex > 0)
		write(1, &tempBuffer[0], *bufferIndex);

	*bufferIndex = 0;
}
