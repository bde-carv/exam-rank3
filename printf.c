/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bde-carv <bde-carv@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 19:22:25 by bde-carv          #+#    #+#             */
/*   Updated: 2022/09/16 19:58:52 by bde-carv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int string(char *str)
{
	int i;

	i = 0;
	if (!str)
	{
		str = "(null)";
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int ft_putnbr_base(long num, char *str, int base)
{
	int length;

	length = 0;

	if (num == 0)
	{
		length += write(1, "0", 1);
		return (length);
	}
	if (num < 0)
	{
		length += write(1, "-", 1);
		num = num * (-1);
	}
	if (num >= base)
	{
		length += ft_putnbr_base((num / base), str, base);
		length += ft_putnbr_base((num % base), str, base);
	}
	else if (num < base)
	{
		length += write(1, &str[num], 1);
	}
	return (length);
}

/*
* ... : indicates that this function can take in a variable number of arguments;
* va_start(list_name, last argument before the variable arguments start): initializes the list; va_end(list_name): terminates the list;
va_arg(list_name, type of the argument): accesses the the next argument;
*/
int	ft_printf(const char *format, ...)
{
	int i;
	int length;
	va_list list;

	i = 0;
	length = 0;
	va_start(list, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
			{
				length += string(va_arg(list, char *));
			}
			else if (format[i] == 'd')
			{
				length += ft_putnbr_base(va_arg(list, int), "0123456789", 10);
			}
			else if (format[i] == 'x')
			{
				length += ft_putnbr_base(va_arg(list, unsigned int), "0123456789abcdef", 16);
			}
			else if (format[i] == '%')
			{
				length += write(1, &format[i], 1);
			}
			i++;
		}
		if (format[i] != '\0' && format[i] != '%')
		{
			length += write(1, &format[i], 1);
			i++;
		}
	}
	va_end(list);
	return (length);
}

// int main()
// {
// 	char *ch = "(a string)";
// 	int i = 0;

// 	i = ft_printf("%d %d %d %d %d", -2147483647, 17, 3, 1300, -400);
// 	ft_printf("\n");
// 	printf("%d\n", i);

// 	i = printf("%d %d %d %d %d", -2147483647, 17, 3, 1300, -400);
// 	printf("\n");
// 	printf("%d\n", i);

// 	i = ft_printf("%x %x %x %x %x", 0, 40, -23, -2147483647, 7);
// 	ft_printf("\n");
// 	printf("%d\n", i);

// 	i = printf("%x %x %x %x %x", 0, 40, -23, -2147483647, 7);
// 	printf("\n");
// 	printf("%d\n", i);

// 	i = ft_printf("Hello this is %s in a string", ch);
// 	ft_printf("\n");
// 	printf("%d\n", i);

// 	i = printf("Hello this is %s in a string", ch);
// 	printf("\n");
// 	printf("%d\n", i);

// 	i = ft_printf("Percentages: %%");
// 	ft_printf("\n");
// 	printf("%d\n", i);

// 	i = printf("Percentages: %%");
// 	printf("\n");
// 	printf("%d\n", i);

// 	printf("\n");
// 	printf("\n");
	
// 	return (0);
// }

int main()
{
	int i;
	int p;
	char *str = "hello";

	i = 0;
	p = 0;
	i = ft_printf("my:%d %d %d %d \n", -2147483647, 0, 40 ,-23);
	p = printf("th:%d %d %d %d \n", -2147483647, 0, 40 ,-23);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	i = ft_printf("my:%x %x %x %x \n", -2147483647, 0, 40 ,-23);
	p = printf("th:%x %x %x %x \n", -2147483647, 0, 40 ,-23);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	i = ft_printf("the word %s is cool\n",str);
	p = printf("the word %s is cool\n", str);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	return (0);
}