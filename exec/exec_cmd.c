#include "../minishell.h"

int	ft_wait_pid(t_data *data)
{
	int	wstatus;
	int	exitstatus;

	while (data->node_pos > 0)
	{
		if (waitpid(-1, &wstatus, 0) == data->pid)
			exitstatus = WEXITSTATUS(wstatus);
		data->node_pos--;
	}
	return (exitstatus);
}

void	ft_exec_builtin(t_list *line, t_data *data)
{
	printf("builtin mon gars\n");
	if (ft_find_word(line->args[0], "cd") == 1)
		ft_cd(line->args, data->env);
	if (ft_find_word(line->args[0], "pwd") == 1)
		ft_pwd();
	if (ft_find_word(line->args[0], "env") == 1)
		ft_env(data->env);
	if (ft_find_word(line->args[0], "echo") == 1)
		ft_echo(line->args);
	if (ft_find_word(line->args[0], "exit") == 1)
		data->rvalue = ft_exit(line->args, line, data->env, data);
	if (ft_find_word(line->args[0], "unset") == 1)
		data->env = ft_unset(line->args, data->env);
	if (ft_find_word(line->args[0], "export") == 1)
		data->env = ft_export(line->args, data->env);
}

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

int	ft_multiples_nodes(t_data *data, int *tmpread, int **fd)
{
	if (data->nodes > 1)
	{
		if (dup2(*tmpread, STDIN_FILENO) == -1)
			return (1);
		if (data->node_pos != data->nodes)
			if (dup2(*fd[1], STDOUT_FILENO) == -1)
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
	while (1)
	{
		if (ft_multiples_nodes(data, &tmpread, &fd))
			break ;
		close(tmpread);
		close(fd[1]);
		if (line->builtin == 1)
			ft_exec_builtin(line, data);
		else if (line->pathname && line->args)
			execve(line->pathname, line->args, envtab);
		break ;
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
		close(fd[1]);
		ft_free_list(&temp);
		ft_free_env(env);
		ft_free_tab(data->paths);
		exit(127);
	}
	close(fd[1]);
	if (data->fdtmp > 2)
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
		if (ft_is_builtin(line) == -1)
			if (ft_test_path(line))
				ft_fill_pathnames(data, line);
		ft_exe(line, temp, env, data);
		line = line->next;
		data->node_pos += 1;
	}
	ft_free_tab(data->paths);
	line = temp;
	return (0);
}
