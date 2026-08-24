/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:25:46 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/28 18:15:40 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	len_src;
	size_t	len_dst;
	int		i;

	len_src = ft_strlen((char *)src);
	len_dst = ft_strlen(dst);
	i = 0;
	if (len_dst < siz)
	{
		while (len_dst + i < siz - 1 && src[i])
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
		return (len_src + len_dst);
	}
	return (siz + len_src);
}
