#include "../../minishell.h"

char	*ft_find_and_exp_var(char *str, char *var, int size, t_data *data)
{
	int		j;
	char	*expand_var;

	j = ft_find_env_var(data->env, var, size);
	if (j == -1)
	{
		if (ft_is_var_only(str) == 1)
		{
			free(var);
			free(str);
			return (NULL);
		}
		else
			expand_var = "";
	}
	else
		expand_var = ft_strdup(data->env[j].data);
	return (expand_var);
}

char	*ft_expand_one_var(char **analysis, char *tabn, int *i, t_data *data)
{
	tabn = ft_replace_env_var(tabn, *i, analysis[0], data);
	if (data->err == 1)
	{
		ft_free_tab(analysis, 0);
		return (NULL);
	}
	if (analysis[0][0] != '\0')
		(*i) += ft_strlen(analysis[0]) - 1;
	return (tabn);
}

char	**ft_expand_dollar(char **tab, int n, int i, t_data *data)
{
	char	**analysis;

	if (tab[n][i + 1] == '?')
		tab[n] = ft_expand_quest_mark(tab[n], i, data);
	else if (ft_is_quote(tab[n][i + 1]) == 1)
		tab[n] = ft_remove_dollar(tab[n], i, data);
	else
	{
		analysis = ft_var_analyse(tab[n], &i, data);
		if (!analysis)
		{
			tab = ft_suppress_empty_arg(tab, n);
			if (!tab[n])
				return (tab);
		}
		else if (analysis[1] == NULL)
			tab[n] = ft_expand_one_var(analysis, tab[n], &i, data);
		else
			tab = ft_realloc_elem(tab, n, analysis, data);
		if (data->err == 1)
			ft_set_error(data, 1);
		ft_free_tab(analysis, 0);
	}
	return (tab);
}

char	**ft_split_env_var(char *str, char *var, t_data *data)
{
	char	**split;
	char	**expand_str;

	split = ft_split_white(var, ' ');
	if (!split)
		ft_set_error(data, 1);
	if (ft_is_redir(str[0]) && split[1] != NULL)
	{
		printf("ambiguous redirect\n");
		return (NULL);
	}
	if (split[1] == NULL)
	{
		expand_str = ft_return_one_str(split[0]);
		ft_free_tab(split, 0);
		return (expand_str);
	}
	else
		return (split);
}

char	**ft_realloc_split(char **new, int *i, char **split, t_data *data)
{
	int	j;

	j = 0;
	while (split[j] != NULL)
	{
		new[*i] = ft_strdup(split[j]);
		if (!new[*i])
			return (ft_set_error(data, 1));
		(*i)++;
		j++;
	}
	return (new);
}
