#include "../../minishell.h"

/* resize the keyword by exluding the doubles chevron (<<).*/

int	ft_malloc_strdup_eof(t_hdoc *infos, char *str) //, t_data *data)
{
	infos->eof = ft_strjoin(NULL, str + 2);
	if (!infos->eof)
	{
		ft_dprintf(2, "malloc fail\n");
		return (0);
	}
	return (1);
}

int	ft_prompt_hdoc(t_data *data, char *tmp, t_hdoc *infos)
{
	if (!tmp)
	{
		data->rvalue = 0;
		infos->str = NULL;
		ft_dprintf(2, "warning: (wanted '%s')\n", infos->eof);
		return (1);
	}
	infos->str = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!infos->str)
	{
		ft_dprintf(2, "join str '\n' fail\n");
		return (1);
	}
	return (0);
}

/* read what we write in the heredoc and add a \n to the string.*/

int	ft_reading_line(int eof_quote, t_hdoc *infos, t_data *data)
{
	char	*tmp;

	rl_event_hook = event;
	tmp = readline("> ");
	rl_event_hook = 0;
	if (g_errvalue == 130)
	{
		data->rvalue = g_errvalue;
		free(tmp);
		return (0);
	}
	if (ft_prompt_hdoc(data, tmp, infos))
	{
		if (tmp)
			free(tmp);
		return (0);
	}
	if (eof_quote == 0)
		infos->str = ft_expand_heredoc(infos->str, data);
	if (data->err == 1)
		return (-1);
	infos->size = ft_strlen(infos->str);
	if (infos->size == 1)
		infos->size++;
	return (1);
}

int	ft_reopen_hdoc(t_list *line, t_hdoc *infos)
{
	close(line->fd_hdoc);
	line->fd_hdoc = open(infos->filename, O_RDONLY, 0644);
	if (line->fd_hdoc == -1)
	{
		unlink(infos->filename);
		free(infos->filename);
		if (infos->str)
			free(infos->str);
		if (infos->eof)
			free(infos->eof);
		ft_dprintf(2, "reopen hd fail\n");
		return (0);
	}
	return (1);
}

/* This heredoc function resize the keyword by exluding the
 * doubles chevron (<<), create a file with random name,
 * write into this file with readline, stop the writing
 * when the keyword (eof) is written and keep the filename
 * in a double tab to unlink them at the end of the cmd line. */

int	ft_heredoc(t_list *line, t_hdoc *infos, t_data *data)
{
	int	i;

	i = 1;
	modify_signals_hdoc();
	while (i <= line->hdoc)
	{
		if (!ft_malloc_strdup_eof(infos, line->redir[i - 1]))
			return (1);
		if (!ft_copy_herefile(line, infos))
			return (1);
		while (1)
		{
			if (!ft_reading_line(line->quote[i - 1], infos, data))
				break ;
			if (!ft_strncmp(infos->eof, infos->str, infos->size - 1))
				break ;
			ft_putstr_fd(infos->str, line->fd_hdoc);
			free(infos->str);
		}
		ft_init_var(infos, 0);
		i++;
	}
	if (!ft_reopen_hdoc(line, infos))
		return (1);
	return (0);
}
