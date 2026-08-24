/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 17:34:03 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/30 17:00:36 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len_s;
	char	*str;

	len_s = (int)ft_strlen((char *)s);
	str = (char *)s + len_s;
	while (len_s >= 0)
	{
		if (*str == (char)c)
			return (str);
		str--;
		len_s--;
	}
	return (0);
}
