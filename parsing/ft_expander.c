#include "../minishell.h"

// Realloc la string en remplacant la variable d'environnement par son expansion
// 		Utilisée dans expand_var_env
char	*ft_replace_env_var(char *str, int *i, char *expand_var, int var_size)
{
	char	*new;
	int		j;

	j = -1;
	new = malloc(sizeof(char *) * (ft_strlen(str)
				- (var_size + 1) + ft_strlen(expand_var) + 1));
	if (!new)
		return (NULL);
	while (++j < *i)
		new[j] = str[j];
	while (expand_var[j - *i] != '\0')
	{
		new[j] = expand_var[j - *i];
		j++;
	}
	*i += var_size + 1;
	while (str[*i] != '\0')
	{
		new[j] = str[*i];
		j++;
		(*i)++;
	}
	new[j] = '\0';
	free(str);
	free(expand_var);
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
	int		var_size;
	char	*expand_var;

	var_size = ft_env_var_len(str, *i + 1);
	var = ft_substr(str, *i + 1, var_size);
	j = 0;
	//INTEGRER LA FONCTION DE JOAN POUR LA RECHERCHE
	while (ft_strncmp(env[j].name, var, ft_strlen(var)) != 0)
		j++;
	if (env[j].name == NULL)
		expand_var = "";
	else
	{
		expand_var = ft_strdup(env[j].data);
		//protection retour de fonction
	}
	free(var);
	str = ft_replace_env_var(str, i, expand_var, var_size);
	return (str);
}

// Gere les cas d'expansion de variables d'environnement avec des quotes
// 		Cherche la fin de la quote et expand les variables d'env trouvées
// 		en chemin seulement si on est entre double quotes ""
// 		Realloc en enlevant les quotes
char	*ft_expand_quote(char *str, int *i, t_env *env)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
	{
		if (str[*i] == '$' && quote == '"')
			str = ft_expand_env_var(str, i, env);
		(*i)++;
	}
	str = ft_remove_quotes(str, quote);
	(*i) -= 2;
	return (str);
}


//Expand les variables d'env et le contenu des quotes suivant le cas
//	Fournit l'input prêt a être envoyé a l'exec
char	*ft_expander(char *str, t_env *env)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		while (ft_is_quote(str[i]) == 0 && str[i] != '$' && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (str);
		if (str[i] == '$')
			str = ft_expand_env_var(str, &i, env);
		if (ft_is_quote(str[i]) == 1)
			str = ft_expand_quote(str, &i, env);
		if (str[i] != '\0')
			i++;
	}
	return (str);
}
