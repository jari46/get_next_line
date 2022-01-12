#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	save = read_file(save, fd);
	if (save == NULL)
		return (NULL);
	if (*save)
	{
		line = get_line(save);
		if (line == NULL)
			return (NULL);
		temp = save;
		save = ft_strdup(save + ft_strlen(line));
		free(temp);
		temp = NULL;
		if (save == NULL)
			return (NULL);
		return (line);
	}
	free(save);
	save = NULL;
	return (NULL);
}

char	*read_file(char *save, int fd)
{
	char	*buf;
	ssize_t	nread;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	nread = 0;
	while (save == NULL || !ft_strchr(save, '\n')
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
			break;
		temp = save;
		buf[nread] = '\0';
		save = ft_strjoin(temp, buf);
		free(temp);
	}
	free(buf);
	buf = NULL;
	if (nread < 0)
		return (NULL);
	return (save);
}

char	*get_line(char *save)
{
	char	*line;
	size_t	len;

	if (ft_strchr(save, '\n'))
	{
		len = ft_strchr(save, '\n') - save + 1;
	}
	else
	{
		len = ft_strchr(save, '\0') - save;
	}
	line = malloc(len + 1);
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, save, len + 1);
	return (line);
}
