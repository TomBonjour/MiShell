#include "../minishell.h"

char	**ft_tab_memset(char **tab, char val, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		tab[i][0] = val;
		i++;
	}
	return (tab);
}

char	**ft_heredoc_priority(char **redir_tab, int size, int j, char *heredoc)
{
	char	**new_tab;
	int		i;

	i = 1;
	new_tab = malloc(sizeof(char *) * (size + 1));
	if (!new_tab)
		return (NULL);
	new_tab[0] = ft_strdup(heredoc);
	if (!new_tab[0])
		return (NULL);
	while (i <= j)
	{
		if (redir_tab[i - 1] != NULL)
		{
			new_tab[i] = ft_strdup(redir_tab[i - 1]);
			if (!new_tab[i])
				return (NULL);
		}
		i++;
	}
	ft_reverse_free(redir_tab, j + 1);
	return (new_tab);
}
