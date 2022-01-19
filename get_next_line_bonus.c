/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:30:30 by yehan             #+#    #+#             */
/*   Updated: 2022/01/20 08:19:29 by yehan            ###   ########.fr       */
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
	node->save = read_iter(node->save, fd);
	if (node->save == NULL || *(node->save) == '\0')
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
	if (set_remains(&node, ft_strlen(line)) == NULL)
		return (NULL);
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

char	*read_iter(char *save, int fd)
{
	char	*buf;
	ssize_t	nread;
	char	*new;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	nread = 0;
	new = save;
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
	if (nread < 0)
		return (NULL);
	return (new);
}

char	*get_line(char const *save)
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

char	*set_remains(t_list **node, size_t offset)
{
	char	*temp;

	temp = (*node)->save;
	(*node)->save = malloc(ft_strlen(temp + offset) + 1);
	if ((*node)->save == NULL)
	{
		free(temp);
		temp = NULL;
		del_node(node);
		return (NULL);
	}
	ft_strlcpy((*node)->save, temp + offset, ft_strlen(temp + offset) + 1);
	free(temp);
	temp = NULL;
	return ((*node)->save);
}
