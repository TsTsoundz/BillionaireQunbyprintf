#include "main.h"

/************************* PRINT CHAR *************************/

int print_char(va_list argslist, char tempBuffer[], int activieFlags,
              int textwidth, int valuePrecision, int typeSize)
{
    char c = va_arg(argslist, int);

    return (handle_write_char(c, tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
}

/************************* PRINT A STRING *************************/

int print_string(va_list argslist, char tempBuffer[], int activieFlags,
                 int textwidth, int valuePrecision, int typeSize)
{
    int length = 0, i;
    char *str = va_arg(argslist, char *);

    UNUSED(tempBuffer);
    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(valuePrecision);
    UNUSED(typeSize);

    if (str == NULL)
    {
        str = "(null)";
        if (valuePrecision >= 6)
            str = "      ";
    }

    while (str[length] != '\0')
        length++;

    if (valuePrecision >= 0 && valuePrecision < length)
        length = valuePrecision;

    if (textwidth > length)
    {
        if (activieFlags & F_MINUS)
        {
            write(1, &str[0], length);
            for (i = textwidth - length; i > 0; i--)
                write(1, " ", 1);
            return (textwidth);
        }
        else
        {
            for (i = textwidth - length; i > 0; i--)
                write(1, " ", 1);
            write(1, &str[0], length);
            return (textwidth);
        }
    }

    return (write(1, str, length));
}

/************************* PRINT PERCENT SIGN *************************/

int print_percent(va_list argslist, char tempBuffer[], int activieFlags,
                   int textwidth, int valuePrecision, int typeSize)
{
    UNUSED(argslist);
    UNUSED(tempBuffer);
    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(valuePrecision);
    UNUSED(typeSize);

    return (write(1, "%%", 1));
}

/************************* PRINT INT *************************/

int print_int(va_list argslist, char tempBuffer[], int activieFlags,
              int textwidth, int valuePrecision, int typeSize)
{
    int i = BUFF_SIZE - 2;
    int is_negative = 0;
    long int n = va_arg(argslist, long int);
    unsigned long int num;

    n = convert_size_number(n, typeSize);

    if (n == 0)
        tempBuffer[i--] = '0';

    tempBuffer[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        is_negative = 1;
    }

    while (num > 0)
    {
        tempBuffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (write_number(is_negative, i, tempBuffer, activieFlags, textwidth, valuePrecision, typeSize));
}

/************************* PRINT BINARY *************************/

int print_binary(va_list argslist, char tempBuffer[], int activieFlags,
                 int textwidth, int valuePrecision, int typeSize)
{
    unsigned int n, m, i, sum;
    unsigned int a[32];
    int count;

    UNUSED(tempBuffer);
    UNUSED(activieFlags);
    UNUSED(textwidth);
    UNUSED(valuePrecision);
    UNUSED(typeSize);

    n = va_arg(argslist, unsigned int);
    m = 2147483648; /* (2 ^ 31) */
    a[0] = n / m;

    for (i = 1; i < 32; i++)
    {
        m /= 2;
        a[i] = (n / m) % 2;
    }

    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += a[i];
        if (sum || i == 31)
        {
            char z = '0' + a[i];
            write(1, &z, 1);
            count++;
        }
    }

    return (count);
}
