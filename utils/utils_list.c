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
	new_elem->quote = NULL;
	new_elem->quote_hdoc = 0;
	new_elem->hdoc = 0;
	new_elem->fd_hdoc = 0;
	new_elem->builtin = 0;
	new_elem->inf = 0;
	new_elem->fd_infile = 0;
	new_elem->outf = 0;
	new_elem->fd_outfile = 0;
	new_elem->pathname = NULL;
	new_elem->realloc = 0;
	new_elem->next = NULL;
	if (ft_get_cmd_and_redir(cmd, i, &new_elem, data) == NULL && data->err == 1)
		return (new_elem);
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
		while ((*line)->args && (*line)->args[i] != NULL)
		{
			free((*line)->args[i]);
			i++;
		}
		free((*line)->args);
		i = 0;
		while ((*line)->redir && (*line)->redir[i] != NULL)
		{
			free((*line)->redir[i]);
			i++;
		}
		free((*line)->redir);
		free((*line)->quote);
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
	g_errvalue = 0;
	data->err = 0;
	data->fdtmp = 0;
	data->pid = 0;
	data->nodes = 1;
	data->node_pos = 1;
	data->rvalue = 0;
}
