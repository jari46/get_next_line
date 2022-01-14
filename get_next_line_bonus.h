# include <unistd.h>
# include <stdlib.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
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
char	*read_file(char *save, int fd);
char	*get_line(char *save);
char	*reset_save(t_list **node, int offset);
void	free_node(t_list **node);
char	*realloc_save(char const *save, char const *buf);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
