#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdlib.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 100
#endif

char    *get_next_line(int fd);
char    *read_file(char *save, int fd);
char    *get_line(char *save);
char	*reset_save(char **save, int offset);
char	*add_buf(char const *save, char const *buf);
size_t	ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

#endif