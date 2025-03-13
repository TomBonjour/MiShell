#include "../minishell.h"

// Realloc la string en remplacant la variable d'environnement par son expansion
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
	i += var_size + 1;
	while (str[i] != '\0')
	{
		new[j] = str[i];
		j++;
		i++;
	}
	free(str);
	free(expand_var);
	return (new);
}

// Recherche la variable var dans le tableau d'environnement, et renvoie une string
// avec son contenu
char	*ft_expand_env_var(char *var, t_env *env)
{
	int		i;
	char	*data;

	i = 0;
	while (ft_strncmp(env[i].name, var, ft_strlen(var)) != 0)
		i++;
	if (env[i].name == NULL)
		data = "";
	else
	{
		data = ft_strdup(env[i].data);
		//protection retour de fonction
	}
	free(var);
	return (data);
}

/*char	*ft_expand_quote(char *str, int i, t_env *env)
{
	char	quote;
	
	quote = str[i];
	while (str[i] != quote)
	{
		if (str[i] == '$')
		{

		}
		i++;
	}

}*/


char	*ft_expander(char *str, t_env *env)
{
	int		i;
	int		var_size;
	char	*var;
	char	*expand_var;

	i = 0;
	while (ft_is_quote(str[i]) == 0 && str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (str);
	if (str[i] == '$')
	{
		var_size = ft_env_var_len(str, i + 1);
		var = ft_substr(str, i + 1, var_size);
		expand_var = ft_expand_env_var(var, env);
		str = ft_replace_env_var(str, i, expand_var, var_size);
	}
	// if (ft_is_quote(str[i]) == 1)
		// str = ft_expand_quote(str, i, env);
		// ft_remove_quote(str, &i);
	return (str);
}
