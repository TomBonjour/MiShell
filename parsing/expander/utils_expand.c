#include "../../minishell.h"

// Renvoie la longueur du nom d'une variable d'env
int	ft_env_var_len(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i] == '_' || ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1)
	{
		size++;
		i++;
	}
	return (size);
}

// Regarde dans une string si il y a une variable d'env ou des quotes
int	ft_need_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_quote(str[i]) == 1
			|| (str[i] == '$' && ft_is_xpendable(str[i + 1])))
			return (1);
		else
			i++;
	}
	return (0);
}

char	*ft_remove_dollar(char *str, int i, t_data *data)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) - 1 + 1));
	if (!new)
		return (ft_set_error(data, 1));
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	i++;
	while (str[i] != '\0')
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

char	**ft_var_analyse(char *str, int *i, t_data *data)
{
	char	*var;
	int		var_size;
	int		j;

	var_size = ft_env_var_len(str, *i + 1);
	var = ft_substr(str, *i + 1, var_size);
	if (!var)
		return (ft_set_error(data, 1));
	j = ft_find_env_var(data->env, var, var_size);
	free(var);
	if (j == -1)
	{
		if (ft_is_var_only(str) == 1)
			return (NULL);
		else
			return (ft_return_one_str("", data));
	}
	else
		return (ft_split_env_var(str, data->env[j].data, data));
}

char	**ft_realloc_elem(char **tab, int n, char **split, t_data *data)
{
	int		i;
	char	**new;

	i = -1;
	new = malloc(sizeof(char *) * (ft_tablen(tab) + ft_tablen(split) - 1 + 1));
	if (!new)
		return (ft_set_error(data, 1));
	while (++i < n)
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (ft_set_error(data, 1));
	}
	split = ft_split_join(split, tab, n, data);
	new = ft_realloc_split(new, &i, split, data);
	while (tab[++n] != NULL)
	{
		new[i] = ft_strdup(tab[n]);
		if (!new[i])
			return (ft_set_error(data, 1));
		i++;
	}
	new[i] = NULL;
	ft_free_tab(tab, 0);
	return (new);
}
