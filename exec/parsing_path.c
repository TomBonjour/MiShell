#include "../minishell.h"

int	ft_cmd_not_found(t_list *line, t_data *data, char *cmd, int i)
{
	char 	path[PATH_MAX];

	if (!data->paths || !data->paths[i])
	{
		if (getcwd(path, PATH_MAX) == NULL)
			return (1);
		if (ft_get_pathname(line, path, cmd))
			return (1);
		if (access(line->pathname, F_OK) == 0)
			return (0);
		ft_dprintf(2, "command not found: %s\n", line->args[0]);
		ft_free_tab(line->args);
		free(line->pathname);
		line->pathname = NULL;
		line->args = NULL;
		data->rvalue = 127;
	}
	return (0);
}

int	ft_pars_env(t_data *data)
{
	int		i;

	i = ft_find_env_var(data->env, "PATH", 4);
	data->node_pos = 1;
	if (i != -1)
	{
		data->paths = ft_split(data->env[i].data, ':');
		if (!data->paths)
		{
			ft_dprintf(2, "Malloc fail\n");
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
		ft_dprintf(2, "Malloc fail\n");
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
		ft_dprintf(2, "Malloc fail\n");
		return (1);
	}
	if (line->pathname == NULL && data->paths)
	{
		while (data->paths[++i])
		{
			if (ft_get_pathname(line, data->paths[i], cmdash))
				return (1);
			if (access(line->pathname, F_OK) == 0)
				break ;
			free(line->pathname);
		}
	}
	if (ft_cmd_not_found(line, data, cmdash, i))
		return (1);
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
