/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:59:30 by mleineku          #+#    #+#             */
/*   Updated: 2025/06/11 17:46:38 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean(char **stash)
{
	char	*line;
	size_t	i;
	size_t	j;
	char	*rest;

	i = 0;
	j = 0;
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = (*stash)[j];
		j++;
	}
	line[j] = '\0';
	rest = ft_strdup(*stash + i);
	free(*stash);
	*stash = rest;
	return (line);
}

void	ft_switchup(char **stash, char **buffer)
{
	char	*tmp;

	tmp = ft_strdup(*stash);
	free(*stash);
	*stash = ft_strjoin(tmp, *buffer);
	free(tmp);
	free(*buffer);
}

int	tchek(int fd, char **stash)
{
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(*stash);
		*stash = NULL;
		return (0);
	}
	return (1);
}
