#include "../minishell.h"

int	ft_find_equal(char *var, t_data *data)
{
	int	numinus;
	int	i;

	i = 0;
	numinus = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '-')
			numinus++;
		if (var[i] == '=' && numinus == 0)
			return (0);
		i++;
	}
	if (numinus != 0)
	{
		ft_dprintf(2, "%s: not a valid identifier\n", var);
		data->rvalue = 1;
	}
	return (1);
}

t_env	*ft_realloc_env(int i)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * (i + 1));
	if (!new)
	{
		ft_dprintf(2, "malloc fail\n");
		return (NULL);
	}
	new[i].name = NULL;
	new[i].data = NULL;
	return (new);
}

int	ft_unset_find_var(char *var, t_env *env)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (env[i].name != NULL)
	{
		if (size == ft_strlen(env[i].name))
		{
			j = 0;
			while (var[j] == env[i].name[j]
				&& (j < size || env[i].name[j] != '\0'))
				j++;
			if (!ft_strncmp(var, env[i].name, size))
				return (0);
		}
		i++;
	}
	return (1);
}

void	ft_unset_fill_env(t_env *new, char *var, t_env *env, int i)
{
	int	j;
	int	k;
	int	size;

	j = 0;
	k = 0;
	while (k < i)
	{
		size = ft_strlen(env[k].name);
		if (!ft_strncmp(var, env[k].name, size))
		{
			free(env[k].name);
			free(env[k].data);
			k++;
		}
		new[j] = env[k];
		j++;
		k++;
	}
}

t_env	*ft_unset(char **argv, t_env *env)
{
	int		i;
	int		j;
	t_env	*new;

	j = 1;
	new = NULL;
	while (argv[j])
	{
		if (!ft_unset_find_var(argv[j], env))
		{
			i = 0;
			while (env[i].name != NULL)
				i++;
			if (!ft_alloc_newenv(&new, i - 1))
				return (NULL);
			ft_unset_fill_env(new, argv[j], env, i);
			free(env);
			env = new;
		}
		j++;
	}
	return (env);
}
