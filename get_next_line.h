#include <unistd.h>  //read
#include <stdlib.h> //malloc, free

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif

char    *get_next_line(int fd);
char    *read_file(char *save, int fd);
char    *get_line(char *save);
size_t	ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);