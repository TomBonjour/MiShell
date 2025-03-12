#include "../minishell.h"

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
	return (data);
}

char	*ft_env_var_substr(char *str, int i, t_env *env)
{
	char	*var;
	char	*expand_var;
	int		size;

	size = 0;
	while (str[i] == '_' || ft_isalpha(str[i]) == 1)
	{
		size++;
		i++;
	}
	i -= size;
	var = ft_substr(str, i, size);
	expand_var = ft_expand_env_var(var, env);
	return (expand_var);
}

void	ft_expander(char *str, t_env *env)
{
	int		i;
	char	*expand_var;

	i = 0;
	while (ft_is_quote(str[i]) == 0 && str[i] != '$' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return ;
	if (str[i] == '$')
	{
		expand_var = ft_env_var_substr(str, i + 1, env);
		// + ft_replace_env_var;
	}
	/*if (ft_is_quote(str[i]) == 1)
		ft_remove_quote(str, &i);*/
}
