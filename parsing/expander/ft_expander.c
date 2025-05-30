#include "../../minishell.h"

int	ft_find_env_var(t_env *env, char *var, int var_size)
{
	int	j;
	int	i;

	i = 0;
	while (env[i].name != NULL)
	{
		if (var_size == ft_strlen(env[i].name))
		{
			j = 0;
			while (var[j] == env[i].name[j]
				&& (j < var_size || env[i].name[j] != '\0'))
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
char	*ft_replace_env_var(char *str, int i, char *exp, t_data *data)
{
	char	*new;
	int		j;
	int		len;

	if (str[i + 1] == '?')
		len = 1;
	else
		len = ft_env_var_len(str, i + 1);
	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen(str) - len + ft_strlen(exp) + 2));
	if (!new)
		return (ft_set_error(data, 1));
	while (++j < i)
		new[j] = str[j];
	while (exp[j - i] != '\0')
	{
		new[j] = exp[j - i];
		j++;
	}
	i += len + 1;
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
char	*ft_expand_env_var(char *str, int *i, t_data *data)
{
	char	*var;
	int		var_size;
	char	*expand_var;

	var_size = ft_env_var_len(str, *i + 1);
	var = ft_substr(str, *i + 1, var_size);
	if (!var)
		return (ft_set_error(data, 1));
	expand_var = ft_find_and_exp_var(str, var, var_size, data);
	free(var);
	str = ft_replace_env_var(str, *i, expand_var, data);
	if (data->err == 1)
	{
		free(expand_var);
		return (NULL);
	}
	if (expand_var[0] != '\0')
	{
		*i += ft_strlen(expand_var) - 1;
		free(expand_var);
	}
	return (str);
}

char	*ft_expand_quest_mark(char *str, int i, t_data *data)
{
	char	*expand_var;

	if (g_errvalue != 0)
		data->rvalue = g_errvalue;
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
char	**ft_expander(char **tab, int n, t_data *data)
{
	int		i;

	i = 0;
	while (tab[n][i] != '\0')
	{
		while (ft_is_quote(tab[n][i]) == 0 && tab[n][i] != '$'
			&& tab[n][i] != '\0')
			i++;
		if (tab[n][i] == '$' && ft_is_xpendable(tab[n][i + 1]) == 1)
		{
			tab = ft_expand_dollar(tab, n, i, data);
			if (!tab[n])
				break ;
		}
		else if (ft_is_quote(tab[n][i]) == 1)
			tab[n] = ft_expand_quote(tab[n], &i, data);
		else if (tab[n][i] != '\0')
			i++;
	}
	return (tab);
}
