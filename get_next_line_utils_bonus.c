
#include "get_next_line_bonus.h"

//t_list	*ft_lstnew(int fd)
//{
//	t_list	*new;

//	new = malloc(sizeof(t_list));
//	if (new == NULL)
//		return (NULL);
//	new->fd = fd;
//	new->save = NULL;
//	return (new);
//}

t_list	*find_node(t_list *head, int fd)
{
	t_list	*lst;

	lst = head->next;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		else
			lst = lst->next;
	}
	lst = ft_lstnew_gnl(fd); //없으면 추가하고
	if (lst == NULL)
		return (NULL);
	lst->next = head->next;
	head->next = lst;
	return (lst);
}

ft_lstdelone()

void	reset_save(char *save, int offset)
{

		temp = lst->save;
		lst->save = ft_strdup(lst->save + ft_strlen(line));
		free(temp);
		temp = NULL;
		if (lst->save == NULL)
			return (NULL);