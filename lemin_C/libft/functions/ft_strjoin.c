/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:56:15 by mleineku          #+#    #+#             */
/*   Updated: 2025/06/09 17:40:29 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*join;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	join = malloc(lens1 + lens2 + 1);
	if (!join)
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		join[i] = s1[i];
		i++;
	}
	while (i < lens1 + lens2)
	{	
		join[i++] = *s2;
		s2++;
	}
	join[i] = '\0';
	return (join);
}
