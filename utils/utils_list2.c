#include "libft.h"
#include <minishell.h>


// Copie du nom de la variable dans la partie "name" de la structure
int	ft_copy_env_name(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '=')
		(*i)++;
	// env[j].name = malloc(sizeof(char) * (*i + 1));
	if (!env[j].name)
		return (-1);
	env[j].name[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].name[*i] = envp[j][*i];
		(*i)--;
	}
	return (0);
}

// Copie du contenu de la variable dans la partie "data" de la structure t_env
int	ft_copy_env_data(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '\0')
		(*i)++;
	(*i) -= ft_strlen(env[j].name) + 1;
	env[j].data = malloc(sizeof(char) * (*i + 1));
	if (!env[j].data)
		return (-1);
	env[j].data[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].data[*i] = envp[j][*i + ft_strlen(env[j].name) + 1];
		(*i)--;
	}
	return (0);
}

// Création du nouveau tableau de variables d'environnement
// --> un tableau de structures {char *name ; char *data}
t_env	*ft_set_env(char **envp, t_data *data)
{
	int		i;
	int		j;
	t_env	*env;

	j = 0;
	while (envp[j] != NULL)
		j++;
	env = malloc(sizeof(t_env) * (j + 1));
	if (!env)
		return (ft_set_error(data, 1));
	j = 0;
	while (envp[j] != NULL)
	{
		i = 0;
		if (ft_copy_env_name(envp, env, j, &i) == -1)
			return (ft_set_error(data, 1));
		i = ft_strlen(env[j].name) + 2;
		if (ft_copy_env_data(envp, env, j, &i) == -1)
			return (ft_set_error(data, 1));
		j++;
	}
	env[j].name = NULL;
	env[j].data = NULL;
	return (env);
}
