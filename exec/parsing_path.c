#include "../minishell.h"

void	ft_cmd_not_found(t_list *line, t_data *data)
{
	printf("command not found: %s\n", line->args[0]);
	ft_free_tab(line->args);
	line->pathname = NULL;
	line->args = NULL;
	data->rvalue = 127;
}

int	ft_pars_env(t_env *env, t_data *data)
{
	int		i;

	i = ft_find_env_var(env, "PATH", 4);
	data->node_pos = 1;
	if (i != -1)
	{
		data->paths = ft_split(env[i].data, ':');
		if (!data->paths)
		{
			printf("Malloc fail\n");
			return (1);
		}
		return (0);
	}
	data->paths = NULL;
	return (0);
}

int	ft_get_pathname(t_list *line, char *path, char *cmdash)
{
	line->pathname = ft_strjoin(path, cmdash);
	if (!line->pathname)
	{
		printf("Malloc fail\n");
		return (1);
	}
	return (0);
}

int	ft_fill_pathnames(t_data *data, t_list *line)
{
	char	*cmdash;
	int		i;

	i = -1;
	cmdash = ft_strjoin("/", line->args[0]);
	if (!cmdash)
	{
		printf("Malloc fail\n");
		return (1);
	}
	if (data->paths)
	{
		while (data->paths[++i])
		{
			if (ft_get_pathname(line, data->paths[i], cmdash))
				return (1);
			if (access(line->pathname, X_OK) == 0)
				break ;
			free(line->pathname);
		}
	}
	if (!data->paths || !data->paths[i])
		ft_cmd_not_found(line, data);
	free(cmdash);
	return (0);
}

int	ft_test_path(t_list *line)
{
	if (line->args[0] == 0)
		return (1);
	if (access(line->args[0], X_OK) == 0)
	{
		if (!ft_get_pathname(line, NULL, line->args[0]))
			return (0);
	}
	return (1);
}
