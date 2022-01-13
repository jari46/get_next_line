#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char			*line;
	static t_list	head;
	t_list			*lst;
	char			*temp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	lst = find_node(&head, fd); //노드를 찾는다 없으면 새로 할당
	if (lst == NULL)
		return (NULL);
	lst->save = read_file(fd, lst->save); //save를 재할당해준다
	if (lst->save == NULL)
		return (NULL);
	else if (*(lst->save)) //save에 뭔가가 들어있다면
	{
		line = get_line(lst->save);
		if (line == NULL)
		{
			ft_lstdelone(lst);
			return (NULL);
		}
		reset_save(&(lst->save), ft_strlen(line));
		return (line);
	}
	free(lst->save); //빈문자열일 때 NULL로 만들어주자.
	lst->save = NULL;
	return (NULL);
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