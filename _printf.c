#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
/**
 * Printf: int_printf function tkes a format string and variable number of arguments using the stdarg.h libarary
 * formart: @formart
 * Return: return void
 */

int int_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
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

int main()
{
    size_t currentTime;
    time(&currentTime);
    
    struct tm *localTime = localtime(&currentTime);
    
    int_printf("Current time: %02d:%02d:%02d\n", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    
    return 0;
}
