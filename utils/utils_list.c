#include "../minishell.h"

// Malloc le nouveau node et remplit les tableaux de commandes et de redir
t_list	*ft_lst_new_node(char *cmd, t_data *data)
{
	t_list	*new_elem;
	int		i;

	i = 0;
	new_elem = malloc(sizeof(t_list) * 1);
	if (!new_elem)
		return (ft_set_error(data, 1));
	new_elem->args = NULL;
	new_elem->redir = NULL;
	if (ft_get_cmd_and_redir(cmd, i, &new_elem, data) == NULL && data->err == 1)
		return (NULL);
	new_elem->next = NULL;
	return (new_elem);
}

// Free la liste
void	ft_free_list(t_list **line)
{
	int		i;
	t_list	*temp;

	i = 0;
	while (*line != NULL)
	{
		temp = (*line)->next;
		i = 0;
		while ((*line)->args[i] != NULL)
		{
			free((*line)->args[i]);
			i++;
		}
		free((*line)->args);
		i = 0;
		while ((*line)->redir[i] != NULL)
		{
			free((*line)->redir[i]);
			i++;
		}
		free((*line)->redir);
		free(*line);
		*line = temp;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

void	ft_init_data(t_data *data)
{
	data->rvalue = 0;
	data->err = 0;
	data->hdoc = 0;
}
