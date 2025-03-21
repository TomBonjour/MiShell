#include "../../minishell.h"

int	ft_find_env_var(t_env *env, char *var)
{
	int	j;
	int	i;
	int	size;

	size = 0;
	i = 0;
	while (var[size] != '\0')
		size++;
	while (env[i].name != NULL)
	{
		if (size == ft_strlen(env[i].name))
		{
			j = 0;
			while (var[j] == env[i].name[j]
				&& (j < size || env[i].name[j] != '\0'))
				j++;
			if (var[j] == '\0' && env[i].name[j] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

// Realloc la string en remplacant la variable d'environnement par son expansion
// 		Utilisée dans expand_var_env
char	*ft_replace_env_var(char *str, int i, char *expand_var, t_data *data)
{
	char	*new;
	int		j;
	int		var_size;

	var_size = ft_env_var_len(str, i + 1);
	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen(str)
				- (var_size + 1) + ft_strlen(expand_var) + 1));
	if (!new)
		return (ft_set_error(data, 1));
	while (++j < i)
		new[j] = str[j];
	while (expand_var[j - i] != '\0')
	{
		new[j] = expand_var[j - i];
		j++;
	}
	i += var_size + 1;
	while (str[i] != '\0')
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

// Expand une variable d'environnement
// 		Recupere le nom de la variable d'env
// 		La retrouve dans le tableau d'env
// 		Realloc la string dans laquelle elle se situe avec son vrai contenu
char	*ft_expand_env_var(char *str, int *i, t_env *env, t_data *data)
{
	int		j;
	char	*var;
	char	*expand_var;
	int		var_size;

	j = 0;
	var_size = ft_env_var_len(str, *i + 1);
	var = ft_substr(str, *i + 1, var_size);
	if (!var)
		return (ft_set_error(data, 1));
	if (ft_find_env_var(env, var) == -1)
		expand_var = "";
	else
		expand_var = ft_strdup(env[j].data);
	free(var);
	str = ft_replace_env_var(str, *i, expand_var, data);
	if (data->err == 1)
	{
		free(expand_var);
		return (NULL);
	}
	*i += ft_strlen(expand_var) - 1;
	if (expand_var[0] != '\0')
		free(expand_var);
	return (str);
}

void	*ft_expand_question_mark(char *str, int i, t_data *data)
{
	char	*expand_var;

	expand_var = ft_itoa(data->rvalue);
	if (!expand_var)
	{
		free(expand_var);
		return (ft_set_error(data, 1));
	}
	str = ft_replace_env_var(str, i, expand_var, data);
	free(expand_var);
	return (str);
}

//Expand les variables d'env et le contenu des quotes suivant le cas
//	Fournit l'input prêt a être envoyé a l'exec
char	*ft_expander(char *str, t_env *env, t_data *data)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_is_quote(str[i]) == 0 && str[i] != '$' && str[i] != '\0')
			i++;
		if (str[i] == '$' && ft_is_xpendable(str[i + 1]) == 1)
		{
			if (str[i + 1] == '?')
				str = ft_expand_question_mark(str, i, data);
			else if (ft_is_quote(str[i + 1]) == 1)
				str = ft_remove_dollar(str, i, data);
			else
				str = ft_expand_env_var(str, &i, env, data);
			if (data->err == 1)
				return (NULL);
		}
		if (ft_is_quote(str[i]) == 1)
			str = ft_expand_quote(str, &i, env, data);
		if (str[i] != '\0')
			i++;
	}
	return (str);
}
