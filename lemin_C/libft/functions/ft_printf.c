/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 18:24:14 by mleineku          #+#    #+#             */
/*   Updated: 2025/05/20 18:00:25 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	implement(char c)
{
	if (c == 'c')
		return (1);
	if (c == 's')
		return (2);
	if (c == 'p')
		return (3);
	if (c == 'd')
		return (4);
	if (c == 'i')
		return (5);
	if (c == 'u')
		return (6);
	if (c == 'x')
		return (7);
	if (c == 'X')
		return (8);
	if (c == '%')
		return (9);
	return (0);
}

void	print(va_list ap, int i, int *count)
{
	if (i == 1)
	{
		ft_putchar_fd(va_arg(ap, int), 1);
		(*count)++;
	}
	if (i == 2)
		ft_putstr(va_arg(ap, char *), count);
	if (i == 3)
		printf_memmory(va_arg(ap, void *), count);
	if (i == 4 || i == 5)
		ft_putnbr(va_arg(ap, int), count);
	if (i == 6)
		unsigned_print((unsigned int)va_arg(ap, int), count);
	if (i == 7)
		print_number_hexa((unsigned int)va_arg(ap, int), count);
	if (i == 8)
		print_upper_hexa(va_arg(ap, unsigned int), count);
	if (i == 9)
	{
		write(1, "%", 1);
		(*count)++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && implement(format[i + 1]) != 0)
		{
			print(args, implement(format[i + 1]), &count);
			i++;
		}
		else
		{
			ft_putchar_fd(format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
