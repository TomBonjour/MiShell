#include "../minishell.h"

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
char	*ft_replace_env_var(char *str, int i, char *expand_var, int var_size)
{
	char	*new;
	int		j;

	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen(str)
				- (var_size + 1) + ft_strlen(expand_var) + 1));
	if (!new)
		return (NULL);
	while (++j < i)
		new[j] = str[j];
	while (expand_var[j - i] != '\0')
	{
		new[j] = expand_var[j - i];
		j++;
	}
	if (str[i] == '$' && str[i + 1] == '?')
		free(expand_var);
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
char	*ft_expand_env_var(char *str, int *i, t_env *env)
{
	int		j;
	char	*var;
	char	*expand_var;
	int		var_size;

	var_size = ft_env_var_len(str, *i + 1);
	var = ft_substr(str, *i + 1, var_size);
	j = ft_find_env_var(env, var);
	if (j == -1)
		expand_var = "";
	else
	{
		expand_var = ft_strdup(env[j].data);
		//protection retour de fonction
	}
	free(var);
	str = ft_replace_env_var(str, *i, expand_var, var_size);
	*i += ft_strlen(expand_var) - 1;
	if (expand_var[0] != '\0')
		free(expand_var);
	return (str);
}

// Gere les cas d'expansion de variables d'environnement avec des quotes
// 		Cherche la fin de la quote et expand les variables d'env trouvées
// 		en chemin seulement si on est entre double quotes ""
// 		Realloc en enlevant les quotes
char	*ft_expand_quote(char *str, int *i, t_env *env, t_data *data)
{
	char	quote;
	int		nb_quote;
	int		pos;

	quote = str[*i];
	pos = *i;
	nb_quote = 0;
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
	{
		if (str[*i] == '$' && quote == '"' && ft_is_xpendable(str[*i + 1]) == 1)
		{
			if (str[*i + 1] == '?')
				str = ft_replace_env_var(str, *i, ft_itoa(data->rvalue), 1);
			else if (ft_is_quote(str[*i + 1]) == 1)
				str = ft_remove_dollar(str, *i);
			else
				str = ft_expand_env_var(str, i, env);
		}
		(*i)++;
	}
	str = ft_remove_quotes(str, quote, pos, nb_quote);
	(*i) -= 2;
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
		if (str[i] == '\0')
			return (str);
		if (str[i] == '$' && ft_is_xpendable(str[i + 1]) == 1)
		{
			if (str[i + 1] == '?')	
				str = ft_replace_env_var(str, i, ft_itoa(data->rvalue), 1);
			else if (ft_is_quote(str[i + 1]) == 1)
				str = ft_remove_dollar(str, i);
			else
				str = ft_expand_env_var(str, &i, env);
		}
		if (ft_is_quote(str[i]) == 1)
			str = ft_expand_quote(str, &i, env, data);
		if (str[i] != '\0')
			i++;
	}
	return (str);
}
