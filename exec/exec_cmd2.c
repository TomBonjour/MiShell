#include "../minishell.h"

int	ft_check_dots(t_data *data, char *str)
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
	data->rvalue = 127;
	return (1);
}

int	ft_wait_pid(t_data *data)
{
	int	wstatus;
	int	exit_status;

	// exit_status = data->rvalue;
	exit_status = 0;
	while (data->node_pos > 1)
	{
		if (waitpid(-1, &wstatus, 0) == data->pid)
		{
			if (WIFSIGNALED(wstatus))
				exit_status = g_errvalue;
			else
				exit_status = WEXITSTATUS(wstatus);
		}
		data->node_pos--;
	}
	if (data->rvalue != 0)
		return (data->rvalue);
	else
		return (exit_status);
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

void	ft_clear_node(t_list *line, t_data *data, t_hdoc *infos)
{
	if (line->pathname)
		free(line->pathname);
	if (line->hdoc != 0)
	{
		if (infos->eof)
			free(infos->eof);
		unlink(infos->filename);
		free(infos->filename);
	}
	ft_close_fds(data, 1);
	data->node_pos += 1;
}

int	ft_reset_data(t_data *data)
{
	ft_free_tab(data->paths, 0);
	if (data->fdtmp > 2)
		close(data->fdtmp);
	data->fdtmp = 0;
	return (0);
}
