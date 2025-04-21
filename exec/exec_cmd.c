#include "../minishell.h"

int	ft_exec_builtin(t_list *line, t_data *data)
{
	if (ft_find_word(line->args[0], "cd") == 1)
		ft_cd(line->args, data->env, data);
	else if (ft_find_word(line->args[0], "pwd") == 1)
		ft_pwd();
	else if (ft_find_word(line->args[0], "env") == 1)
		ft_env(data->env);
	else if (ft_find_word(line->args[0], "echo") == 1)
		ft_echo(line->args);
	else if (ft_find_word(line->args[0], "exit") == 1)
		data->rvalue = ft_exit(line, data->env, data);
	else if (ft_find_word(line->args[0], "unset") == 1)
		data->env = ft_unset(line->args, data->env);
	else if (ft_find_word(line->args[0], "export") == 1)
		data->env = ft_export(line->args, data);
	if (dup2(STDOUT_FILENO, 1) == -1 || dup2(STDIN_FILENO, 0) == -1)
		return (1);
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
		if (ft_multi_nodes(line, data, &tmpread, fd))
			break ;
		if (tmpread != 0)
			close(tmpread);
		close(fd[1]);
		if (ft_is_builtin_child(line))
			ft_exec_builtin(line, data);
		if (line->pathname && line->args && line->builtin == 0)
			execve(line->pathname, line->args, envtab);
		break ;
	}
	ft_free_child(line, data, fd);
	ft_reverse_free(envtab, i);
}

int	ft_exe(t_list *line, t_list *temp, t_data *data)
{
	int		fd[2];
	char	**envtab;
	int		j;

	if (ft_init_exe(data, fd))
		return (1);
	modify_signals_execve();
	if (data->pid == 0)
	{
		reset_signals();
		envtab = ft_convert_env(data);
		if (envtab)
			ft_child_process(line, envtab, data, fd);
		j = line->builtin;
		ft_free_list(&temp);
		if (j == 1)
			exit(data->rvalue);
		exit(127);
	}
	close(fd[1]);
	if (data->fdtmp > 2)
		close(data->fdtmp);
	data->fdtmp = fd[0];
	return (0);
}

void	ft_parsexec(t_list *line, t_data *data, t_list *temp)
{
	if (ft_is_builtin_parent(line) == 1 && data->nodes == 1)
		ft_exec_builtin(line, data);
	if (ft_pars_dir(line, data, line->args[0]) && line->args[0])
	{
		if (line->pathname == NULL && line->builtin != -1
			&& ft_is_builtin_child(line) != 1)
			ft_fill_pathnames(data, line);
		// if (data->rvalue != 127)
		ft_exe(line, temp, data);
	}
}

int	ft_exec_cmd(t_list *line, t_data *data)
{
	t_hdoc	infos;
	t_list	*temp;

	temp = line;
	if (ft_pars_env(data))
		return (1);
	while (line != NULL)
	{
		data->rvalue = 0;
		if (ft_open_redir(line, &infos, data) != -1)
			ft_parsexec(line, data, temp);
		ft_clear_node(line, data, &infos);
		line = line->next;
	}
	ft_reset_data(data);
	line = temp;
	return (0);
}
