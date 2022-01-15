#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

typedef struct s_list
{
	int				fd;
	char			*save;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);
t_list	*get_node(t_list *head, int fd);
char	*read_file(char const *save, int fd);
char	*get_line(char const *save);
char	*reset_save(t_list **node, size_t offset);
void	free_node(t_list **node);
char	*append_buf(char const *save, char const *buf);
size_t	ft_strlen(char const *s);
char	*ft_strchr(char const *s, int c);
size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize);

#endif