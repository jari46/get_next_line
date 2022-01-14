#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	head;
	t_list			*node;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	node = get_node(&head, fd);
	if (node == NULL)
		return (NULL);
	node->save = read_file(node->save, fd);
	if (node->save == NULL || *(node->save) == '\0')
	{
		free_node(&node);
		return (NULL);
	} 
	line = get_line(node->save);
	if (line == NULL)
	{
		free_node(&node);
		return (NULL);
	}
	if (reset_save(&node, ft_strlen(line)) == NULL)
		return (NULL);
	return (line);
}

t_list	*get_node(t_list *head, int fd)
{
	t_list	*node;
	t_list	*new;

	if (head->next)
	{
		node = head->next;
		while (node)
		{
			if (node->fd == fd)
				return (node);
			else
				node = node->next;
		}
	}
	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->prev = head;
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
		save = add_buf(save, buf);
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

char	*reset_save(t_list **node, int offset)
{
	char	*temp;

	temp = (*node)->save;
	(*node)->save = malloc(ft_strlen(temp + offset) + 1);
	if ((*node)->save == NULL)
	{
		free(temp);
		temp = NULL;
		free_node(node);
		return (NULL);
	}
	ft_strlcpy((*node)->save, temp + offset, ft_strlen(temp + offset) + 1);
	free(temp);
	temp = NULL;
	return ((*node)->save);
}