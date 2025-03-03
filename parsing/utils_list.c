/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 08:02:20 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/03 20:00:41 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_lstnew(char *cmd)
{
	t_list	*new_elem;

	new_elem = malloc(sizeof(t_list) * 1);
	if (!new_elem)
		return (0);
	new_elem->args = NULL;
	new_elem->redir = NULL;
	if (ft_get_command_and_redir(cmd, &new_elem) == -1)
		return (0);
	new_elem->next = NULL;
	return (new_elem);
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

void	ft_lstadd_back(t_list **lst, t_list *lstnew)
{
	t_list	*last;

	if (!lst || !lstnew)
		return ;
	last = ft_lstlast(*lst);
	if (!last)
		*lst = lstnew;
	else
		last->next = lstnew;
}

int	ft_lstsize(t_list *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		size++;
	}
	return (size);
}

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
