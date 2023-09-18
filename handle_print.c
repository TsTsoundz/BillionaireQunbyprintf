#include "main.h"

/**
 * handle_print - Prints an argument based on its type
 * @inputFmt: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * @argslist: List of arguments to be printed
 * @tempBuffer: Buffer array to handle print
 * @activeFlags: Calculates active flags
 * @textwidth: get width
 * @valuePrecision: Precision specification
 * @typeSize: Size specifier
 *
 * Return: 1 or 2;
 */
int handle_print(const char *inputFmt, int *counter, va_list argslist, char tempBuffer[],
        int activeFlags, int textwidth, int valuePrecision, int typeSize)
{
    int i, unknownLen = 0, printedChars = -1;
    fmt_t fmtTypes[] = {
        {'c', print_char}, {'s', print_string}, {'%', print_percent},
        {'i', print_int}, {'d', print_int}, {'b', print_binary},
        {'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
        {'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
        {'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
    };

    for (i = 0; fmtTypes[i].fmt != '\0'; i++)
    {
        if (inputFmt[*counter] == fmtTypes[i].fmt)
        {
            return fmtTypes[i].fn(argslist, tempBuffer, activeFlags, textwidth, valuePrecision, typeSize);
        }
    }

    if (fmtTypes[i].fmt == '\0')
    {
        if (inputFmt[*counter] == '\0')
        {
            return -1;
        }

        unknownLen += write(1, "%", 1);

        if (inputFmt[*counter - 1] == ' ')
        {
            unknownLen += write(1, " ", 1);
        }
        else if (textwidth)
        {
            (*counter)--;

            while (inputFmt[*counter] != ' ' && inputFmt[*counter] != '%')
            {
                (*counter)--;
            }

            if (inputFmt[*counter] == ' ')
            {
                (*counter)--;
            }

            return 1;
        }

        unknownLen += write(1, &inputFmt[*counter], 1);

        return unknownLen;
    }

    return printedChars;
}
