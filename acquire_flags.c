#include "main.h"

/**
 * acquire_flags - function that prints flag
 * @format: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * Return: activeFlags:
 */
int acquire_flags(const char *format, int *counter)
{
int j, currCounter;
int activeFlags = 0;
const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

for (currCounter = *counter + 1; format[currCounter] != '\0'; currCounter++)

{
for (j = 0; FLAGS_CH[j] != '\0'; j++)
{
if (format[currCounter] == FLAGS_CH[j])
{
activeFlags |= FLAGS_ARR[j];
break;
}
}
if (FLAGS_CH[j] == '\0')
{
break;
}
}
*counter = currCounter - 1;
return (activeFlags);
}
