#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1000
#endif

char    *get_next_line(int fd);
char    *read_file(char *save, int fd);
char    *get_line(char const *save);
char	*reset_save(char **save, size_t offset);
char	*append_buf(char const *save, char const *buf);
size_t	ft_strlen(char const *s);
char    *ft_strchr(char const *s, int c);
size_t	ft_strlcpy(char *dst, char const *src, size_t dstsize);

#endif