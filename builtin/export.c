#include "../minishell.h"

int	ft_first_char(char *var)
{
	int	i;

	i = 0;
	if (!var || var[0] == '\0')
	{
		ft_dprintf(2, "export: not valid in this context: %s\n", var);
		return (1);
	}
	else if (var[0] == '=')
	{
		ft_dprintf(2, "%s, not found\n", var + 1);
		return (1);
	}
	else if (var[0] < '0' && var[0] > '9' && var[0] != '_')
	{
		ft_dprintf(2, "export: not an identidier: %s\n", var);
		return (1);
	}
	return (0);
}

int	ft_forbidd_char(char *var, t_data *data)
{
	int	i;

	i = 0;
	if (ft_first_char(var))
	{
		data->rvalue = 1;
		return (1);
	}
	while (var[i] != '\0')
	{
		if (var[i] == ' ')
		{
			ft_dprintf(2, "export: not valid in this context: %s\n", var);
			data->rvalue = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_replace_data(t_env *env, char *var, int *i, int j)
{
	free(env[*i].data);
	env[*i].data = ft_strdup(var + j + 1);
	if (!env[*i].data)
		ft_dprintf(2, "malloc fail\n");
}

int	ft_join_data(t_env *env, char *var, int *i, int j)
{
	char	*tmp;

	tmp = ft_strjoin(env[*i].data, var + j + 2);
	if (!tmp)
		ft_dprintf(2, "malloc fail\n");
	free(env[*i].data);
	env[*i].data = tmp;
	return (0);
}

int	ft_compare_data(t_env *env, char *var, int *i, int j)
{
	if (var[j] == '+' && var[j + 1] == '=' && env[*i].name[j] == '\0')
	{
		ft_join_data(env, var, i, j);
		return (1);
	}
	else if (var[j] == '=' && env[*i].name[j] == '\0')
	{
		ft_replace_data(env, var, i, j);
		return (1);
	}
	return (0);
}

int	ft_find_var(t_env *env, char *var, int *i)
{
	int	j;
	int	size;

	size = 0;
	while (var[size] != '=' && var[size] != '+' && var[size] != '\0')
		size++;
	while (env[*i].name != NULL)
	{
		if (size == ft_strlen(env[*i].name))
		{
			j = 0;
			while (var[j] == env[*i].name[j]
				&& (j < size || env[*i].name[j] != '\0'))
				j++;
			if (ft_compare_data(env, var, i, j))
				return (1);
		}
		(*i)++;
	}
	return (0);
}

int	ft_export_fill_env(t_env *new, char *var, t_env *env)
{
	int	j;

	j = 0;
	while (env[j].name != NULL)
	{
		new[j] = env[j];
		j++;
	}
	new[j].name = ft_fill_name(var, 1);
	if (!new[j].name)
	{
		ft_dprintf(2, "malloc fail\n");
		return (1);
	}
	new[j].data = ft_fill_name(var, 0);
	if (!new[j].data)
	{
		ft_dprintf(2, "malloc fail\n");
		return (1);
	}
	return (0);
}

int	ft_checking_args(char *var, t_data *data)
{
	int	index;

	index = 0;
	if (!ft_forbidd_char(var, data))
		if (!ft_find_var(data->env, var, &index))
			if (!ft_find_equal(var, data))
				return (0);
	return (1);
}

t_env	*ft_export(char **argv, t_data *data)
{
	t_env	*new;
	int		i;
	int		j;

	j = 1;
	new = NULL;
	while (argv[j])
	{
		i = 0;
		if (!ft_checking_args(argv[j], data))
		{
			while (data->env[i].name != NULL)
				i++;
			if (!ft_alloc_newenv(&new, i + 1))
				return (NULL);
			ft_export_fill_env(new, argv[j], data->env);
			free(data->env);
			data->env = new;
		}
		j++;
	}
	return (data->env);
}

int ft_alloc_newenv(t_env **new, int i)
{
	*new = ft_realloc_env(i);
	if (!*new)
	{
		ft_dprintf(2, "malloc fail\n");
		return (0);
	}
	return (1);
}
