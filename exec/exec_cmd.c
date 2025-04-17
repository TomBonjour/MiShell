#include "../minishell.h"
#include <unistd.h>

int	ft_wait_pid(t_data *data)
{
	int	wstatus;
	// int	exitstatus;

	while (data->node_pos > 0)
	{
		if (waitpid(-1, &wstatus, 0) == data->pid)
			g_errvalue = WEXITSTATUS(wstatus);
		data->node_pos--;
	}
	// if (g_errvalue == 127)
		// return (g_errvalue);
	if (g_errvalue == 0)
		return (g_errvalue);
	else
		return (g_errvalue);
}

int	ft_init_exe(t_data *data, int *fd)
{
	if (data->fdtmp == 0)
		data->fdtmp = STDIN_FILENO;
	if (pipe(fd) == -1)
	{
		ft_dprintf(2, "init pipe fail\n");
		return (1);
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		ft_dprintf(2, "init fork fail\n");
		return (1);
	}
	return (0);
}

int	ft_multiples_nodes(t_list *line, t_data *data, int *tmpread, int *fd)
{
	if (data->nodes > 1)
	{
		if (data->node_pos != 1)
			if (dup2(*tmpread, STDIN_FILENO) == -1)
				return (1);
		if (data->node_pos != data->nodes)
			if (dup2(fd[1], STDOUT_FILENO) == -1)
				return (1);
	}
	if (line->hdoc || line->inf)
	{
		if (ft_exec_infiles(line) == 1)
			return (1);
		if (line->fd_infile != 0 && line->fd_infile != -1)
			close(line->fd_infile);
		if (line->fd_hdoc != 0 && line->fd_hdoc != -1)
			close(line->fd_hdoc);
	}
	if (line->outf)
	{
		if (dup2(line->fd_outfile, STDOUT_FILENO) == -1)
			return (1);
		close(line->fd_outfile);
	}
	return (0);
}

int	ft_exec_builtin(t_list *line, t_data *data)
{
	// if (line->outf)
	// {
		// if (dup2(line->fd_outfile, STDOUT_FILENO) == -1)
			// return (1);
		// close(line->fd_outfile);
	// }
	if (ft_find_word(line->args[0], "cd") == 1)
		ft_cd(line->args, data->env);
	else if (ft_find_word(line->args[0], "pwd") == 1)
		ft_pwd();
	else if (ft_find_word(line->args[0], "env") == 1)
		ft_env(data->env);
	else if (ft_find_word(line->args[0], "echo") == 1)
		ft_echo(line->args);
	else if (ft_find_word(line->args[0], "exit") == 1)
		g_errvalue = ft_exit(line, data->env, data);
	else if (ft_find_word(line->args[0], "unset") == 1)
		data->env = ft_unset(line->args, data->env);
	else if (ft_find_word(line->args[0], "export") == 1)
		data->env = ft_export(line->args, data);
	if (dup2(STDOUT_FILENO, 1) == -1 || dup2(STDIN_FILENO, 0) == -1)
		return (1);
	return (0);
}

void	ft_free_child(t_list *line, t_data *data, int *fd)
{
	close(line->fd_infile);
	close(line->fd_outfile);
	close(fd[1]);
	close(fd[0]);
	free(line->pathname);
	ft_free_env(data->env);
	ft_free_tab(data->paths, 0);
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
		if (ft_multiples_nodes(line, data, &tmpread, fd))
			break ;
		if (tmpread != 0)
			close(tmpread);
		close(fd[1]);
		if (ft_is_builtin_child(line))
			ft_exec_builtin(line, data);
		if (line->pathname && line->args && line->builtin == 0)
		{
			modify_signals_execve();
			// signal(SIGINT, SIG_DFL);
			// signal(SIGQUIT, SIG_DFL);
			execve(line->pathname, line->args, envtab);
		}
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
	if (data->pid == 0)
	{
		envtab = ft_convert_env(data);
		if (envtab)
			ft_child_process(line, envtab, data, fd);
		j = line->builtin;
		ft_free_list(&temp);
		if (j == 1)
			exit(g_errvalue);
		exit(127);
	}
	close(fd[1]);
	if (data->fdtmp > 2)
		close(data->fdtmp);
	data->fdtmp = fd[0];
	return (0);
}

void	ft_clear_node(t_list *line, t_data *data, t_hdoc *infos)
{
	if (line->pathname)
		free(line->pathname);
	if (line->hdoc != 0)
	{
		unlink(infos->filename);
		free(infos->filename);
	}
	ft_close_fds(data, 1);
	data->node_pos += 1;
}

int	ft_check_dots(char *str)
{
	int	size;

	size = ft_strlen(str);
	while (1)
	{
		if (size == 1 && str[0] == '.')
			break ;
		else if (size == 2 && str[0] == '.' && str[1] == '.')
			break ;
		else
			return (0);
	}
	ft_dprintf(2, "%s: command not found\n", str);
	g_errvalue = 127;
	return (1);
}

int	ft_pars_dir(t_list *line, char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == 0)
		{
			while (str[i] != '\0')
			{
				if (ft_isalnum(str[i]))
					if (!ft_get_pathname(line, NULL, str))
						return (1);
				i++;
			}
			ft_dprintf(2, "%s: Is a directory\n", str);
			g_errvalue = 126;
			return (0);
		}
		g_errvalue = 127;
		ft_dprintf(2, "%s: No such file or directory\n", str);
		return (0);
	}
	else if (ft_check_dots(str))
		return (0);
	return (1);
}

int	ft_reset_data(t_data *data)
{
	ft_free_tab(data->paths, 0);
	if (data->fdtmp > 2)
		close(data->fdtmp);
	data->fdtmp = 0;
	return (0);
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
		g_errvalue = 0;
		if (ft_open_redir(line, &infos, data) != -1)
		{
			if (ft_is_builtin_parent(line) == 1 && data->nodes == 1)
				ft_exec_builtin(line, data);
			if (ft_pars_dir(line, line->args[0]) && line->builtin != 1
				&& line->args[0])
			{
				if (line->pathname == NULL && line->builtin != -1)
					ft_fill_pathnames(data, line);
				if (g_errvalue != 127)
					ft_exe(line, temp, data);
			}
		}
		ft_clear_node(line, data, &infos);
		line = line->next;
	}
	ft_reset_data(data);
	line = temp;
	return (0);
}
