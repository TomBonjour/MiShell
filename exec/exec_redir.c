#include "../minishell.h"

int	ft_open_infile(t_list *line, t_data *data)
{
	int	i;

	i = 0;
	while (line->redir[i] != NULL)
	{
		if (line->redir[i][0] == '<')
		{
			if (line->fd_infile != 0)
				close(line->fd_infile);
			line->fd_infile = open(line->redir[i] + 1, O_RDONLY);
			if (line->fd_infile == -1)
			{
				printf("No such file or directory\n");
				ft_set_error(data, 3);
				return (-1);
			}
		}
		i++;
	}
	return (0);
}

int	ft_open_outfile(t_list *line)
{
	int	i;

	i = 0;
	while (line->redir[i] != NULL)
	{
		if (line->redir[i][0] == '>')
		{
			if (line->fd_outfile != 0)
				close(line->fd_outfile);
			if (line->redir[i][1] == '>')
				line->fd_outfile = open(line->redir[i] + 2,
						O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644);
			else
				line->fd_outfile = open(line->redir[i] + 1,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		i++;
	}
	return (0);
}

int	ft_open_redir(t_list *line, t_hdoc *infos, t_env *env, t_data *data)
{
	if (line->hdoc != 0)
	{
		ft_init_var(infos, 1);
		if (ft_heredoc(line, infos, env, data) == 1)
			return (-1);
	}
	if (line->inf != 0)
	{
		if (ft_open_infile(line, data) == -1)
			return (-1);
	}
	if (line->outf != 0)
	{
		if (ft_open_outfile(line) == -1)
			return (-1);
	}
	return (0);
}
