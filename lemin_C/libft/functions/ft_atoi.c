/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:04:42 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/28 20:13:57 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sign(const char *nptr)
{
	int	i;
	int	count;
	int	sign;

	i = 0;
	count = 0;
	sign = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		count++;
		if (count > 1)
			return (0);
		if (nptr[i] == '-')
		{	
			sign = -1;
		}
		i++;
	}
	return (sign);
}

int	ft_atoi(const char *nptr)
{
	long long	result;
	int			i;

	result = 0;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	while (nptr[i] == '+' || nptr[i] == '-')
	{
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	if (result > 2147483647)
	{
		if (sign(nptr) == 1)
			return (0);
		return (-2147483648);
	}
	return ((int)(sign(nptr) * result));
}
