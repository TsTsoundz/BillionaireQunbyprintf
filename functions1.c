#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/

int print_unsigned(va_list argslist, char tempBuffer[], int activieFlags,
                   int textwidth, int valuePrecision, int typeSize)
{
    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(argslist, unsigned long int);

    num = convert_size_unsgnd(num, typeSize);

    if (num == 0)
        tempBuffer[i--] = '0';

    tempBuffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        tempBuffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_unsgnd(0, i, tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/

int print_octal(va_list argslist, char tempBuffer[], int activieFlags,
                 int textwidth, int valuePrecision, int typeSize)
{
    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(argslist, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(textwidth);

    num = convert_size_unsgnd(num, typeSize);

    if (num == 0)
        tempBuffer[i--] = '0';

    tempBuffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        tempBuffer[i--] = (num % 8) + '0';
        num /= 8;
    }

    if (activieFlags & F_HASH && init_num != 0)
        tempBuffer[i--] = '0';

    i++;

    return (write_unsgnd(0, i, tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/

int print_hexadecimal(va_list argslist, char tempBuffer[], int activieFlags,
                      int textwidth, int valuePrecision, int typeSize)
{
    return (print_hexa(argslist, "0123456789abcdef", tempBuffer, activieFlags, 'x', textwidth, valuePrecision, typeSize));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/

int print_hexa_upper(va_list argslist, char tempBuffer[], int activieFlags,
                      int textwidth, int valuePrecision, int typeSize)
{
    return (print_hexa(argslist, "0123456789ABCDEF", tempBuffer, activieFlags, 'X', textwidth, valuePrecision, typeSize));
}

/************** PRINT HEXX NUM IN LOWER OR UPPER **************/

int print_hexa(va_list argslist, char map_to[], char tempBuffer[], int activieFlags,
               char flag_ch, int textwidth, int valuePrecision, int typeSize)
{
    int i = BUFF_SIZE - 2;
    unsigned long int num = va_arg(argslist, unsigned long int);
    unsigned long int init_num = num;

    UNUSED(textwidth);

    num = convert_size_unsgnd(num, typeSize);

    if (num == 0)
        tempBuffer[i--] = '0';

    tempBuffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        tempBuffer[i--] = map_to[num % 16];
        num /= 16;
    }

    if (activieFlags & F_HASH && init_num != 0)
    {
        tempBuffer[i--] = flag_ch;
        tempBuffer[i--] = '0';
    }

    i++;

    return (write_unsgnd(0, i, tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
}
