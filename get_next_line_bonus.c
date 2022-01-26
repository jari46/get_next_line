/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:30:30 by yehan             #+#    #+#             */
/*   Updated: 2022/01/26 14:31:23 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_list	head;
	t_list			*node;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	node = get_node(&head, fd);
	if (node == NULL)
		return (NULL);
	node->save = read_iter(&(node->save), fd);
	if (node->save == NULL)
	{
		del_node(&node);
		return (NULL);
	}
	line = get_line(node->save);
	if (line == NULL)
	{
		del_node(&node);
		return (NULL);
	}
	node->save = set_remains(&(node->save), ft_strlen(line));
	if (node->save == NULL)
	{
		del_node(&node);
		return (NULL);
	}
	return (line);
}

t_list	*get_node(t_list *head, int fd)
{
	t_list	*node;

	node = head->next;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		else
			node = node->next;
	}
	node = malloc(sizeof(t_list));
	if (node == NULL)
		return (NULL);
	node->fd = fd;
	node->save = NULL;
	node->prev = head;
	node->next = head->next;
	if (head->next)
		head->next->prev = node;
	head->next = node;
	return (node);
}

char	*read_iter(char **save, int fd)
{
	char	*buf;
	ssize_t	nread;
	char	*temp;
	char	*new;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	nread = 0;
	new = *save;
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

char	*get_line(char const *save)
{
	size_t	len;
	char	*line;

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

char	*set_remains(char **save, size_t offset)
{
	char	*new;

	new = malloc(ft_strlen(*save + offset) + 1);
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, *save + offset, ft_strlen(*save + offset) + 1);
	free(*save);
	*save = NULL;
	return (new);
}
