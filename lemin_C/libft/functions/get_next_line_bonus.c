/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleineku <mleineku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:58:54 by mleineku          #+#    #+#             */
/*   Updated: 2025/06/19 13:25:35 by mleineku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	linefinished(char *str)
{
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

char	*readfile(int fd, char **stash)
{
	char	*buffer;
	size_t	bytesread;

	while (linefinished(*stash) != 1)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread] = '\0';
		if (bytesread <= 0)
		{
			free(buffer);
			if (bytesread == 0 && **stash)
				return (*stash);
			return (NULL);
		}
		ft_switchup(stash, &buffer);
	}
	return (*stash);
}

void	clean_fd(char **stash)
{
	int	fd;

	fd = 0;
	while (fd < OPEN_MAX)
	{
		if (stash[fd])
		{
			free(stash[fd]);
			stash[fd] = (NULL);
		}
		fd++;
	}
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (tchek(fd, &stash[fd]) == 0)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!readfile(fd, &stash[fd]) || !*stash[fd] || !stash[fd])
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = clean(&stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}
