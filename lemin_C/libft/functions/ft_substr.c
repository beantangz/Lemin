/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:04:03 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/30 17:36:25 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	min(size_t a, size_t b)
{
	if (a >= b)
		return (b);
	return (a);
}

char	*caca(void)
{
	char	*d;

	d = malloc(1);
	if (!d)
		return (NULL);
	d[0] = '\0';
	return (d);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	len_s;
	char	*d;
	int		taille_copie;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen((char *)s);
	if (start >= (size_t)len_s)
		return (caca());
	taille_copie = min((len), len_s - (size_t)start);
	d = malloc((size_t)taille_copie + 1);
	if (!d)
		return (NULL);
	while (taille_copie > 0)
	{
		d[i] = s[start];
		i++;
		start++;
		taille_copie--;
	}
	d[i] = '\0';
	return (d);
}
