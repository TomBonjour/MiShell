#include "../minishell.h"

char	**ft_replace_heredoc(char **redir_tab, char **new_tab, int size, int *j)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (redir_tab[i][0] == '<' && redir_tab[i][1] == '<')
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

char	**ft_heredoc_prio(char **redir_tab, int size, t_data *data)
{
	char	**new_tab;
	int		j;

	j = 0;
	new_tab = malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (ft_set_error(data, 1));
	new_tab = ft_replace_heredoc(redir_tab, new_tab, size, &j);
	if (!new_tab)
	{
		ft_reverse_free(redir_tab, size);
		return (ft_set_error(data, 1));
	}
	new_tab = ft_replace_redir(redir_tab, new_tab, size, &j);
	if (!new_tab)
	{
		ft_reverse_free(redir_tab, size);
		return (ft_set_error(data, 1));
	}
	new_tab[j] = NULL;
	ft_reverse_free(redir_tab, size);
	return (new_tab);
}
