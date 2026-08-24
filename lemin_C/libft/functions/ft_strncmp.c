/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:37:01 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/28 18:25:32 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	m;

	m = 0;
	if (n == 0)
		return (0);
	while (s1[m] != '\0' && s2[m] != '\0' && m < n)
	{
		if ((unsigned char)s1[m] != (unsigned char)s2[m])
			return ((unsigned char)s1[m] - (unsigned char)s2[m]);
		m++;
	}
	if (m < n)
		return ((unsigned char)s1[m] - (unsigned char)s2[m]);
	return (0);
}
