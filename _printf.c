#include "main.h"
#include <stdio.h>
#include <stdarg.h>

#define BUFF_SIZE 100

void print_buffer(char buffer[], int *buff_ind);


/**

 * int_printf - Printf function

 * @format: format.

 * Return: Printed chars.

 */

int int_printf(const char *format, ...)
{
        int i, printed = 0, printed_chars = 0;
        int flags, width, precision, size, buff_ind = 0;
        va_list list;
        char buffer[BUFF_SIZE];

        if (format == NULL)
                return (-1);

        va_start(list, format);

        for (i = 0; format && format[i] != '\0'; i++)
        {
                if (format[i] != '%' || format[i+1] == '%')
                {
                        buffer[buff_ind++] = format[i];
                        if (buff_ind == BUFF_SIZE)
                                print_buffer(buffer, &buff_ind);
                        printed_chars++;
                }
                else
                {
                        print_buffer(buffer, &buff_ind);
                        flags = get_flags(format, &i);
                        width = get_width(format, &i, list);
                        precision = get_precision(format, &i, list);
                        size = get_size(format, &i);
                        ++i;
                        if (format[i] == 'c')
                        {
                                char c = va_arg(list, int);
                                putchar(c);
                                printed_chars++;
                        }
                        else if (format[i] == 's')
                        {
                                char *s = va_arg(list, char *);
                                fputs(s, stdout);
                                printed_chars += strlen(s);
                        }
                        else if (format[i] == '%')
                        {
                                putchar('%');
                                printed_chars++;
                        }
                }
        }

        print_buffer(buffer, &buff_ind);

        va_end(list);

        return (printed_chars);
}


/**

 * print_buffer - Prints the contents of the buffer if it exists

 * @buffer: Array of chars

 * @buff_ind: Index at which to add next char, represents the length.

 */

void print_buffer(char buffer[], int *buff_ind)
{
        if (*buff_ind > 0)
                write(1, &buffer[0], *buff_ind);

        *buff_ind = 0;
}
