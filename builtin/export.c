#include "../minishell.h"

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
				return (ft_set_error(data, 1));
			ft_export_fill_env(new, argv[j], data->env);
			free(data->env);
			data->env = new;
		}
		j++;
	}
	return (data->env);
}
