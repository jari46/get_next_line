/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehan <yehan@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:28:20 by yehan             #+#    #+#             */
/*   Updated: 2022/01/26 12:35:10 by yehan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_list
{
	int				fd;
	char			*save;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*get_node(t_list *head, int fd);
char	*read_iter(char **save, int fd);
char	*get_line(char const *save);
char	*set_remains(char **save, size_t offset);
void	del_node(t_list **node);
char	*append_buf(char const *save, char const *buf);
size_t	ft_strlen(char const *s);
char	*ft_strchr(char const *s, int c);
size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize);

#endif