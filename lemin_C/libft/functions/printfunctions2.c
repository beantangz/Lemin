/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfunctions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:53:01 by mleineku          #+#    #+#             */
/*   Updated: 2025/05/19 16:11:43 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int *count)
{
	long	l;

	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', 1);
		l = -l;
		(*count)++;
	}
	if (l > 9)
	{
		ft_putnbr(l / 10, count);
	}
	ft_putchar_fd((char)((l % 10) + 48), 1);
	(*count)++;
}

void	ft_putstr(char *c, int *count)
{
	if (c == NULL)
	{
		write(1, "(null)", 6);
		(*count) += 6;
		return ;
	}
	while (*c)
	{
		ft_putchar_fd(*c, 1);
		c++;
		(*count)++;
	}
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
