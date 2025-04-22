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
	else if (var[0] >= '0' && var[0] <= '9' && var[0] != '_')
	{
		ft_dprintf(2, "export: not an identidier: %s\n", var);
		return (1);
	}
	return (0);
}

int	ft_forbidd_char(t_data *data, char *var)
{
	int	i;

	i = 0;
	if (ft_first_char(var))
	{
		data->rvalue = 1;
		return (1);
	}
	return (0);
}

int	ft_checking_args(char *var, t_data *data)
{
	int	index;

	index = 0;
	if (!ft_forbidd_char(data, var))
		if (!ft_find_var(data->env, var, &index))
			if (!ft_find_equal(data, var))
				return (0);
	return (1);
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

int	ft_alloc_newenv(t_env **new, int i)
{
	*new = ft_realloc_env(i);
	if (!*new)
		return (0);
	return (1);
}
