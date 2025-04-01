#include "../../minishell.h"

char	**ft_replace_hdoc(char **tab, char **new_tab, int size, t_list **new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (tab[i][0] == '<' && tab[i][1] == '<')
		{
			(*new)->hdoc += 1;
			new_tab[j] = ft_strdup(tab[i]);
			if (!new_tab[j])
				return (NULL);
			j++;
		}
		else if (tab[i][0] == '<')
			(*new)->inf += 1;
		else if (tab[i][0] == '>')
			(*new)->outf += 1;
		i++;
	}
	return (new_tab);
}

char	**ft_replace_redir(char **redir_tab, char **new_tab, int size, int *j)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (redir_tab[i][0] != '<' || redir_tab[i][1] != '<')
		{
			new_tab[*j] = ft_strdup(redir_tab[i]);
			if (!new_tab[*j])
				return (NULL);
			(*j)++;
		}
		i++;
	}
	return (new_tab);
}

char	**ft_heredoc_prio(char **redir_tab, int nb, t_list **new, t_data *data)
{
	char	**new_tab;
	int		j;

	(*new)->last_infile = ft_last_infile(*new);
	new_tab = malloc(sizeof(char *) * (nb + 1));
	if (!new_tab)
		return (ft_set_error(data, 1));
	new_tab = ft_replace_hdoc(redir_tab, new_tab, nb, new);
	if (!new_tab)
	{
		ft_reverse_free(redir_tab, nb);
		return (ft_set_error(data, 1));
	}
	j = (*new)->hdoc;
	new_tab = ft_replace_redir(redir_tab, new_tab, nb, &j);
	if (!new_tab)
	{
		ft_reverse_free(redir_tab, nb);
		return (ft_set_error(data, 1));
	}
	new_tab[j] = NULL;
	ft_reverse_free(redir_tab, nb);
	return (new_tab);
}
