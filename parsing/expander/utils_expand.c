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
	char	**split;
	char	**expand_str;

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
		{
			expand_str = ft_return_one_str("");
			return (expand_str);
		}
	}
	else
	{
		split = ft_split_white(data->env[j].data, ' ');
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
}

char **ft_realloc_args(t_list *line, int n, char **split, t_data *data)
{
	int		size;
	int		i;
	int		j;
	char	**new;

	size = 0;
	i = 0;
	j = 0;
	while (split[size] != NULL)
		size++;
	new = malloc(sizeof(char *) * (line->nb_args + size - 1 + 1));
	if (!new)
		return (NULL);
	while (i < n)
	{
		new[i] = ft_strdup(line->args[i]);
		i++;
	}
	if (line->args[n][0] != '$')
		split = ft_join_content_before(split, line->args[n], data);
	while (split[j] != NULL)
	{
		new[i] = ft_strdup(split[j]);
		i++;
		j++;
	}
	n++;
	while (line->args[n] != NULL)
	{
		new[i] = ft_strdup(line->args[n]);
		i++;
		n++;
	}
	new[i] = NULL;
	ft_free_tab(line->args, 0);
	return (new);
}
