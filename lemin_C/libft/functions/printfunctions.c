/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfunctions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:29:44 by mleineku          #+#    #+#             */
/*   Updated: 2025/05/19 16:11:39 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_number_hexa(unsigned int l, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (l >= 16)
		print_number_hexa(l / 16, count);
	ft_putchar_fd(hex[l % 16], 1);
	(*count)++;
}

void	print_upper_hexa(unsigned int l, int *count)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (l >= 16)
		print_upper_hexa(l / 16, count);
	ft_putchar_fd(hex[l % 16], 1);
	(*count)++;
}

void	print_memmory_hexa(unsigned long long addr, int *count)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (addr >= 16)
	{
		print_memmory_hexa(addr / 16, count);
	}
	ft_putchar_fd(hex[addr % 16], 1);
	(*count)++;
}

void	printf_memmory(void *ptr, int *count)
{
	if (!ptr)
	{
		write(1, "(nil)", 5);
		(*count) += 5;
	}
	else
	{
		write(1, "0x", 2);
		(*count) += 2;
		print_memmory_hexa((unsigned long long)ptr, count);
	}
}

void	unsigned_print(unsigned int i, int *count)
{
	if (i > 9)
		unsigned_print(i / 10, count);
	ft_putchar_fd((char)((i % 10) + 48), 1);
	(*count)++;
}
