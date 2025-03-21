#include "minishell.h"

int	ft_forbidd_char(char *var)
{
	int	i;

	i = 0;
	while (1)
	{
		if (var[0] == '\0' || var[i] == ' ')
		{
			printf("export: not valid in this context: %s\n", var);
			return (1);
		}
		if (var[i] == '\0')
			break ;
		i++;
	}
	if (var[0] == '=')
	{
		printf("%s not found\n", var + 1);
		return (1);
	}
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		printf("export: not an identifier: %s\n", var);
		return (1);
	}
	return (0);
}

void	ft_replace_data(t_env *env, char *var, int *i, int j)
{
	free(env[*i].data);
	env[*i].data = ft_strdup(var + j + 1);
	if (!env[*i].data)
		printf("malloc fail\n");
}

int	ft_find_var(t_env *env, char *var, int *i)
{
	int	j;
	int	size;

	size = 0;
	while (var[size] != '=' && var[size] != '\0')
		size++;
	while (env[*i].name != NULL)
	{
		if (size == ft_strlen(env[*i].name))
		{
			j = 0;
			while (var[j] == env[*i].name[j]
				&& (j < size || env[*i].name[j] != '\0'))
				j++;
			if (var[j] == '=' && env[*i].name[j] == '\0')
			{
				ft_replace_data(env, var, i, j);
				return (1);
			}
		}
		(*i)++;
	}
	return (0);
}

int	ft_export_fill_env(t_env *new, char *var, t_env *env)
{
	int	j;
	int	c;

	c = 0;
	j = 0;
	while (env[j].name != NULL)
	{
		new[j] = env[j];
		j++;
	}
	new[j].name = ft_fill_name(var, '=');
	if (!new[j].name)
	{
		printf("malloc fail\n");
		return (1);
	}
	new[j].data = ft_fill_data(var, '=');
	if (!new[j].data)
	{
		printf("malloc fail\n");
		return (1);
	}
	return (0);
}

int	ft_checking_args(char *var, t_env *env)
{
	int	index;

	index = 0;
	if (!ft_find_equal(var))
		if (!ft_find_var(env, var, &index))
			if (!ft_forbidd_char(var))
				return (0);
	return (1);
}

t_env	*ft_export(char **argv, t_env *env)
{
	t_env	*new;
	int		i;
	int		j;

	j = 1;
	new = NULL;
	while (argv[j])
	{
		i = 0;
		if (!ft_checking_args(argv[j], env))
		{
			while (env[i].name != NULL)
				i++;
			if (!ft_alloc_newenv(new, i + 1))
				return (NULL);
			ft_export_fill_env(new, argv[j], env);
			free(env);
			env = new;
		}
		j++;
	}
	return (env);
}

int ft_alloc_newenv(t_env *new, int i)
{
	new = ft_realloc_env(i);
	if (!new)
	{
		printf("malloc fail\n");
		return (0);
	}
	return (1);
}
