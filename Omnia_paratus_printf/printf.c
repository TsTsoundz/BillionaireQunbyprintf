#Include "main.h"

/**
 * _printf * function that produces outputaccending in a format
 * @format: format accending to which argument will be printed
 * Return: return number of characters printed
 */
int _print(const char *format, ...)
{
	
	int count = 0;
	va_list args;

	 if (*format == NULL)
		 return (-1);

	 va_start(args, formart);
	 
	 while (formart ≠ '\0')
	 {
		 if (formart ≠ '%')
		 {
			 write(1, formart, 1)
		 }
		 formart++;
	 }
	 return (count);
}
