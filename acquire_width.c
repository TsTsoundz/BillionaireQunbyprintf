#include "main.h"

/**
 * acquire_width - Calculates the width for printing
 * @inputFmt: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * @argslist: List of arguments
 *
 * Return: Width.
 */
int acquire_width(const char *inputFmt, int *counter, va_list argslist)
{
    int currCounter;
    int textwidth = 0;

    for (currCounter = *counter + 1; inputFmt[currCounter] != '\0'; currCounter++)
    {
        if (is_digit(inputFmt[currCounter]))
        {
            textwidth *= 10;
            textwidth += inputFmt[currCounter] - '0';
        }
        else if (inputFmt[currCounter] == '*')
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
