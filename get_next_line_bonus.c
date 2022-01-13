#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	head;
	t_list			*lst;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	lst = get_node(&head, fd);
	if (lst == NULL)
		return (NULL);
	lst->save = read_file(fd, lst->save);
	if (lst->save == NULL || *(lst->save) == '\0')
	{
		free_node(&lst);
		return (NULL);
	} 
	line = get_line(lst->save);
	if (line == NULL || reset_save(&lst, ft_strlen(line)) == NULL)
	{
		free_node(&lst);
		return (NULL);
	}
	return (line);
}

t_list	*get_node(t_list *head, int fd)
{
	t_list	*lst;
	t_list	*new;

	if (head->next)
	{
		lst = head->next;
		while (lst)
		{
			if (lst->fd == fd)
				return (lst);
			else
				lst = lst->next;
		}
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->next = head->next;
	head->next = new;
	return (new);
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
	while (save == NULL || !ft_strchr(save, '\n'))
	{
		nread = read(fd, buf, BUFFER_SIZE);
		if (nread <= 0)
			break ;
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

char	*reset_save(t_list **lst, int offset)
{
	char	*temp;
	char	*save;

	save = (*lst)->save;
	temp = save;
	save = ft_strdup(save + offset);
	free(temp);
	temp = NULL;
	return (save);
}