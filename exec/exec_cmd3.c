/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:28 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:22:15 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_perm_isadir(t_list *line, t_data *data, char *str)
{
	int	i;

	i = 0;
	if (access(str, X_OK) == 0)
	{
		while (str[i] != '\0')
		{
			if (ft_isalnum(str[i]))
				if (!ft_get_pathname(line, NULL, str))
					return (1);
			i++;
		}
		data->rvalue = 126;
		ft_dprintf(2, "%s: Is a directory\n", str);
	}
	else
	{
		data->rvalue = 126;
		ft_dprintf(2, "%s: Permission denied\n", str);
	}
	return (0);
}

int	ft_pars_dir(t_list *line, t_data *data, char *str)
{
	int	i;

	(void)line;
	i = 0;
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == 0)
		{
			if (ft_perm_isadir(line, data, str))
				return (1);
			else
				return (0);
		}
		data->rvalue = 127;
		ft_dprintf(2, "%s: No such file or directory\n", str);
		return (0);
	}
	else if (ft_check_dots(data, str))
		return (0);
	return (1);
}

int	ft_multi_nodes(t_list *line, t_data *data, int *tmpread, int *fd)
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
