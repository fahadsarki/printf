// #include "main.h"
// #include <stdlib.h>
// #include <stdio.h>

// /**
//  * printSpecials - prints special characters
//  * @next: character after the %
//  * @arg: argument for the indentifier
//  * Return: the number of characters printed
//  * (excluding the null byte used to end output to strings)
// */

// int printSpecials(char next, va_list arg)
// {
// 	int functsIndex;

// 	specialsStruct functs[] = {
// 		{"c", print_char},
// 		{"s", print_str},
// 		{"d", print_int},
// 		{"i", print_int},
// 		{"u", print_unsigned},
// 		{"b", print_unsignedToBinary},
// 		{"o", print_oct},
// 		{"x", print_hex},
// 		{"X", print_HEX},
// 		{"S", print_STR},
// 		{NULL, NULL}
// 	};

// 	for (functsIndex = 0; functs[functsIndex].indentifier != NULL; functsIndex++)
// 	{
// 		if (functs[functsIndex].indentifier[0] == next)
// 			return (functs[functsIndex].printer(arg));
// 	}
// 	return (0);
// }

// /**
//  * _printf - mimic printf from stdio
//  * Description: produces output according to a format
//  * write output to stdout, the standard output stream
//  * @format: character string composed of zero or more directives
//  *
//  * Return: the number of characters printed
//  * (excluding the null byte used to end output to strings)
//  * return -1 for incomplete specials error
// */

// int _printf(const char *format, ...)
// {
// 	unsigned int i;
// 	int specialsPrinted = 0, charPrinted = 0;
// 	va_list arg;

// 	va_start(arg, format);
// 	if (format == NULL)
// 		return (-1);

// 	for (i = 0; format[i] != '\0'; i++)
// 	{
// 		if (format[i] != '%')
// 		{
// 			_putchar(format[i]);
// 			charPrinted++;
// 			continue;
// 		}
// 		if (format[i + 1] == '%')
// 		{
// 			_putchar('%');
// 			charPrinted++;
// 			i++;
// 			continue;
// 		}
// 		if (format[i + 1] == '\0')
// 			return (-1);

// 		specialsPrinted = printSpecials(format[i + 1], arg);
// 		if (specialsPrinted == -1 || specialsPrinted != 0)
// 			i++;
// 		if (specialsPrinted > 0)
// 			charPrinted += specialsPrinted;

// 		if (specialsPrinted == 0)
// 		{
// 			_putchar('%');
// 			charPrinted++;
// 		}
// 	}
// 	va_end(arg);
// 	return (charPrinted);
// }

#include "main.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * _printf - produces output according to a format
 * @format: format string containing the characters and the specifiers
 * Description: this function will call the get_print() function that will
 * determine which printing function to call depending on the conversion
 * specifiers contained into fmt
 * Return: length of the formatted output string
 */
int _printf(const char *format, ...)
{
	int (*pfunc)(va_list, flags_t *);
	const char *p;
	va_list arguments;
	flags_t flags = {0, 0, 0};

	register int count = 0;

	va_start(arguments, format);
	
	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = format; *p; p++)
	{
		if (*p == '%')
		{
			p++;
			if (*p == '%')
			{
				count += _putchar('%');
				continue;
			}
			while (get_flag(*p, &flags))
				p++;
			pfunc = get_print(*p);
			count += (pfunc)
				? pfunc(arguments, &flags)
				: _printf("%%%c", *p);
		}
		else
			count += _putchar(*p);
	}
	_putchar(-1);
	va_end(arguments);
	return (count);
}
