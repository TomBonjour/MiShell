#include "../../minishell.h"

int	ft_malloc_strdup_eof(t_heredoc *infos, t_list *line)
{
	infos->eof = ft_strjoin(line->redir[0] + 2, "\n");
	if (!infos->eof)
	{
		printf("malloc fail\n");
		return (0);
	}
	return (1);
}

int	ft_reading_line(t_heredoc *infos, t_env *env, t_data *data)
{
	char	*tmp;

	tmp = readline("> ");
	if (!tmp)
	{
		printf("readline fail\n");
		return (0);
	}
	infos->str = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!infos->str)
	{
		printf("join str '\n' fail\n");
		return (0);
	}
	infos->str = ft_expand_heredoc(infos->str, env, data);
	infos->size = ft_strlen(infos->str);
	return (1);
}

int	ft_file_heredoc(t_heredoc *infos, char **idoc_itoa, int idoc)
{
	*idoc_itoa = ft_itoa(idoc);
	if (!*idoc_itoa)
	{
		free(infos->str);
		printf("itoa idoc heredoc fail\n");
		return (0);
	}
	infos->filename = ft_strjoin("heredoc", *idoc_itoa);
	if (!infos->filename)
	{
		free(infos->str);
		free(*idoc_itoa);
		printf("strjoin file heredoc fail\n");
		return (0);
	}
	return (1);
}

int	ft_copy_herefile(t_heredoc *infos, int idoc)
{
	char	*idoc_itoa;

	idoc_itoa = NULL;
	if (!ft_file_heredoc(infos, &idoc_itoa, idoc))
		return (0);
	infos->fd = open(infos->filename, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (infos->fd == -1)
	{
		free(idoc_itoa);
		free(infos->filename);
		free(infos->str);
		free(infos->eof);
		printf("heredoc fd fail\n");
		return (0);
	}
	free(idoc_itoa);
	return (1);
}

int	ft_heredoc(t_list *line, t_env *env, t_data *data)
{
	t_heredoc	infos;
	static int	idoc;

	ft_init_var(&infos, &idoc, 1);
	if (!ft_malloc_strdup_eof(&infos, line))
		return (1);
	if (!ft_copy_herefile(&infos, idoc))
		return (1);
	while (1)
	{
		if (!ft_reading_line(&infos, env, data))
			return (1);
		if (!ft_strncmp(infos.eof, infos.str, infos.size))
			break ;
		ft_putstr_fd(infos.str, infos.fd);
		free(infos.str);
	}
	ft_init_var(&infos, &idoc, 0);
	idoc++;
	return (0);
}
