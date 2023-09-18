#include "main.h"

/****************** PRINT POINTER ******************/

int print_pointer(va_list argslist, char tempBuffer[], int activieFlags,
                  int textwidth, int valuePrecision, int typeSize)
{
    char extra_c = 0, padd = ' ';
    int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
    unsigned long num_addrs;
    char map_to[] = "0123456789abcdef";
    void *addrs = va_arg(argslist, void *);

    UNUSED(textwidth);
    UNUSED(typeSize);

    if (addrs == NULL)
        return (write(1, "(nil)", 5));

    tempBuffer[BUFF_SIZE - 1] = '\0';
    UNUSED(valuePrecision);

    num_addrs = (unsigned long)addrs;

    while (num_addrs > 0)
    {
        tempBuffer[ind--] = map_to[num_addrs % 16];
        num_addrs /= 16;
        length++;
    }

    if ((activieFlags & F_ZERO) && !(activieFlags & F_MINUS))
        padd = '0';

    if (activieFlags & F_PLUS)
        extra_c = '+', length++;
    else if (activieFlags & F_SPACE)
        extra_c = ' ', length++;

    ind++;

    return (write_pointer(tempBuffer, ind, length, textwidth, activieFlags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/

int print_non_printable(va_list argslist, char tempBuffer[], int activieFlags,
                        int textwidth, int valuePrecision, int typeSize)
{
    int i = 0, offset = 0;
    char *str = va_arg(argslist, char *);

    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(valuePrecision);
    UNUSED(typeSize);

    if (str == NULL)
        return (write(1, "(null)", 6));

    while (str[i] != '\0')
    {
        if (is_printable(str[i]))
            tempBuffer[i + offset] = str[i];
        else
            offset += append_hexa_code(str[i], tempBuffer, i + offset);

        i++;
    }

    tempBuffer[i + offset] = '\0';

    return (write(1, tempBuffer, i + offset));
}

/************************* PRINT REVERSE *************************/

int print_reverse(va_list argslist, char tempBuffer[], int activieFlags,
                   int textwidth, int valuePrecision, int typeSize)
{
    char *str;
    int i, count = 0;

    UNUSED(tempBuffer);
    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(typeSize);

    str = va_arg(argslist, char *);

    if (str == NULL)
    {
        UNUSED(valuePrecision);
        str = ")Null(";
    }

    for (i = 0; str[i]; i++)
        ;

    for (i = i - 1; i >= 0; i--)
    {
        char z = str[i];
        write(1, &z, 1);
        count++;
    }

    return (count);
}

/************************* PRINT A STRING IN ROT13 *************************/

int print_rot13string(va_list argslist, char tempBuffer[], int activieFlags,
                       int textwidth, int valuePrecision, int typeSize)
{
    char x;
    char *str;
    unsigned int i, j;
    int count = 0;
    char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

    str = va_arg(argslist, char *);

    UNUSED(tempBuffer);
    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(valuePrecision);
    UNUSED(typeSize);

    if (str == NULL)
        str = "(AHYY)";

    for (i = 0; str[i]; i++)
    {
        for (j = 0; in[j]; j++)
        {
            if (in[j] == str[i])
            {
                x = out[j];
                write(1, &x, 1);
                count++;
                break;
            }
        }

        if (!in[j])
        {
            x = str[i];
            write(1, &x, 1);
            count++;
        }
    }

    return (count);
}
