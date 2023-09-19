#include "main.h"

/**
 * acquire_flags - function that prints flag
 * get_flags - Calculates active flags
 * @inputFmt: Formatted string in which to print the arguments
 * @counter: Pointer to an integer that keeps track of the current position
 * Return: Flags:
 */
int acquire_flags(const char *inputFmt, int *counter)
{
int j, currCounter;
int activieFlags = 0;
const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

for (currCounter = *counter + 1; inputFmt[currCounter] != '\0'; currCounter++)

{
for (j = 0; FLAGS_CH[j] != '\0'; j++)
{
if (inputFmt[currCounter] == FLAGS_CH[j])
{
activieFlags |= FLAGS_ARR[j];
break;
}
}
if (FLAGS_CH[j] == '\0')
{
break;
}
}
*counter = currCounter - 1;
return (activieFlags);
}
