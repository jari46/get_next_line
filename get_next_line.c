/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:29:33 by yehan             #+#    #+#             */
/*   Updated: 2022/01/26 14:31:21 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*s_save;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	s_save = read_iter(&s_save, fd);
	if (s_save == NULL)
		return (NULL);
	line = get_line(s_save);
	if (line == NULL)
	{
		free(s_save);
		s_save = NULL;
		return (NULL);
	}
	s_save = set_remains(&s_save, ft_strlen(line));
	if (s_save == NULL)
		return (NULL);
	return (line);
}

char	*read_iter(char **s_save, int fd)
{
	char		*buf;
	ssize_t		nread;
	char		*temp;
	char		*new;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(*s_save);
		*s_save = NULL;
		return (NULL);
	}
	nread = 0;
	new = *s_save;
	while (new == NULL || !ft_strchr(new, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
			break ;
		buf[nread] = '\0';
		temp = new;
		new = append_buf(new, buf);
		free(temp);
	}
	free(buf);
	buf = NULL;
	if (nread < 0 || new == NULL || *new == '\0')
	{
		free(new);
		new = NULL;
		return (NULL);
	}
	return (new);
}

char	*get_line(char const *s_save)
{
	size_t		len;
	char		*line;

	if (ft_strchr(s_save, '\n'))
	{
		len = ft_strchr(s_save, '\n') - s_save + 1;
	}
	else
	{
		len = ft_strchr(s_save, '\0') - s_save;
	}
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, s_save, len + 1);
	return (line);
}

char	*set_remains(char **s_save, size_t offset)
{
	char	*new;

	new = malloc(ft_strlen(*s_save + offset) + 1);
	if (new == NULL)
	{
		free(*s_save);
		*s_save = NULL;
		return (NULL);
	}
	ft_strlcpy(new, *s_save + offset, ft_strlen(*s_save + offset) + 1);
	free(*s_save);
	*s_save = NULL;
	return (new);
}
