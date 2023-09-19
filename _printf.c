#include "main.h"

void update_buffer(char tempBuffer[], int *bufferIndex);
/**
 * my_printf - Printf function
 * @inputFmt: inputFmt.
 * Return: totalcharcount.
 */
int my_printf(const char *inputFmt, ...)
{

	int counter, totalCharCount = 0, returnedVal = 0;
	int activieFlags, textwidth, valuePrecision, typeSize, bufferIndex = 0;
	va_list argslist;
	char tempBuffer[BUFF_SIZE];

	if (inputFmt == NULL)
		return (-1);

	va_start(argslist, inputFmt);

	for (counter = 0; inputFmt && inputFmt[counter] != '\0'; counter++)
	{
		if (inputFmt[counter] != '%')
		{
			tempBuffer[bufferIndex++] = inputFmt[counter];
			if (bufferIndex == BUFF_SIZE)
				update_buffer(tempBuffer, &bufferIndex);
			totalCharCount++;
		}
		else
		{
			update_buffer(tempBuffer, &bufferIndex);
			activieFlags = get_flags(inputFmt, &counter);
			textwidth = get_width(inputFmt, &counter, argslist);
			valuePrecision = acquire_precision(inputFmt, &counter, argslist);
			typeSize = acquire_size(inputFmt, &counter);
			++counter;
			returnedVal = (handle_print(inputFmt, &counter, argslist,
			tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
			if (returnedVal == -1)
				return (-1);
			totalCharCount += returnedVal;
		}
	}

	update_buffer(tempBuffer, &bufferIndex);

	va_end(argslist);

	return (totalCharCount);
}
