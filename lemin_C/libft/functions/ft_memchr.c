/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:58:37 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/28 15:45:03 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			m;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	m = 0;
	while (m < n)
	{
		if (*ptr == (unsigned char)c)
			return ((void *)ptr);
		m++;
		ptr++;
	}
	return (0);
}
