#include "../minishell.h"

int	ft_init_exe(t_data *data, int *fd)
{
	if (pipe(fd) == -1)
	{
		printf("init pipe fail\n");
		return (1);
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		printf("init fork fail\n");
		return (1);
	}
	return (0);
}

void	ft_child_process(t_list *line, char **envtab, t_data *data, int *fd)
{
	int	tmpread;
	int	i;

	i = 0;
	while (envtab[i])
		i++;
	close(fd[0]);
	tmpread = data->fdtmp;
	if (dup2(tmpread, STDIN_FILENO) != -1)
	{
		if (dup2(fd[1], STDOUT_FILENO) != -1)
		{
			close(tmpread);
			close(fd[1]);
			if (line->pathname && line->args)
				execve(line->pathname, line->args, envtab);
		}
	}
	ft_reverse_free(envtab, i);
}

int	ft_exe(t_list *line, t_list *temp, t_env *env, t_data *data)
{
	int		fd[2];
	char	**envtab;

	if (ft_init_exe(data, fd))
		return (1);
	if (data->pid == 0)
	{
		envtab = ft_convert_env(env, data);
		if (envtab)
			ft_child_process(line, envtab, data, fd);
		ft_free_list(&temp);
		ft_free_env(env);
		exit(127);
	}
	close(fd[1]);
	if (data->fdtmp != -1)
		close(data->fdtmp);
	data->fdtmp = fd[0];
	return (0);
}

int	ft_exec_cmd(t_list *line, t_env *env, t_data *data)
{
	t_hdoc	infos;
	t_list	*temp;

	temp = line;
	if (ft_pars_env(env, data))
		return (1);
	while (line != NULL)
	{
		if (line->hdoc != 0)
		{
			ft_init_var(&infos, 1);
			ft_heredoc(line, &infos, env, data);
		}
		if (ft_test_path(line))
			ft_fill_pathnames(data, line);
		ft_exe(line, temp, env, data);
		line = line->next;
	}
	return (0);
}
