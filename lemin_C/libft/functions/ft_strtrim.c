/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:46:49 by mleineku          #+#    #+#             */
/*   Updated: 2025/04/30 17:19:26 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	search(const char s, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (0);
		i++;
	}
	return (1);
}

size_t	first_count(const char *s1, char const *set)
{
	size_t	count;

	count = 0;
	while (*s1 && search(*s1, set) == 0)
	{
		count++;
		s1++;
	}
	return (count);
}

size_t	last_count(const char *s1, const char *set)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = ft_strlen((char *)s1);
	while (search(s1[i - 1], set) == 0 && i > 0)
	{
		count++;
		i--;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count_first_set;
	size_t	count_last_set;
	char	*trimmed;
	size_t	size_trimmed;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	count_first_set = first_count(s1, set);
	count_last_set = last_count(s1, set);
	if (count_first_set + count_last_set >= ft_strlen((char *)s1))
		return (ft_strdup(""));
	size_trimmed = ft_strlen((char *)s1) - count_first_set - count_last_set;
	trimmed = malloc(size_trimmed + 1);
	if (!trimmed)
		return (NULL);
	while (i < size_trimmed)
	{
		trimmed[i] = s1[i + count_first_set];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
