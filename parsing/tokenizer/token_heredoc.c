#include "../../minishell.h"

char	**ft_replace_hdoc(char **redir_tab, char **new_tab, int size, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (redir_tab[i][0] == '<' && redir_tab[i][1] == '<')
		{
			data->hdoc += 1;
			new_tab[j] = ft_strdup(redir_tab[i]);
			if (!new_tab[j])
				return (NULL);
			j++;
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

	new_tab = malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (ft_set_error(data, 1));
	new_tab = ft_replace_hdoc(redir_tab, new_tab, size, data);
	if (!new_tab)
	{
		ft_reverse_free(redir_tab, size);
		return (ft_set_error(data, 1));
	}
	j = data->hdoc;
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
