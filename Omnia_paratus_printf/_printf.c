#include "main.h"
#include <stdio.h>
#include <stdarg.h>
 
 void print_buffer (char buffer[]; int*buff_ind);
/**
*_printf -Printf function
*@format: format
*Return(): Printed chars.
*/

int _printf(const char *format, ...) 
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
    va_list args;
    va_start(args, format, ...);
    char buffer [BUFF_SIZE];
    
    int printed_chars = 0;
    
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            
            // Handle the conversion specifiers
            switch (*format) {
                case 'c': {
                    // Print a single character
                    int c = va_arg(args, int);
                    putchar(c);
                    printed_chars++;
                    break;
                }
                case 's': {
                    // Print a string
                    char *s = va_arg(args, char*);
                    fputs(s, stdout);
                    printed_chars += strlen(s);
                    break;
                }
                case '%': {
                    // Print a percent sign
                    putchar('%');
                    printed_chars++;
                    break;
                }
                default:
                    // Invalid conversion specifier, ignore it
                    break;
            }
        } else {
            // Print regular characters
            putchar(*format);
            printed_chars++;
        }
        
        format++;
    }
    
    va_end(args);
    
    return printed_chars;
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */


int main() {
    _printf("Today, %s! we made it work %c.\n", "BillQun", 'M');
    return 0;
}

