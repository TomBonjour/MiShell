#include "../../minishell.h"

/* resize the keyword by exluding the doubles chevron (<<).*/

int	ft_malloc_strdup_eof(t_hdoc *infos, char *str)
{
	infos->eof = ft_strjoin(str + 2, "\n");
	if (!infos->eof)
	{
		printf("malloc fail\n");
		return (0);
	}
	return (1);
}

/* read what we write in the heredoc and add a \n to the string.*/

int	ft_reading_line(t_hdoc *infos, t_env *env, t_data *data)
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
	if (data->err == 1)
		return (-1);
	infos->size = ft_strlen(infos->str);
	return (1);
}

/* write the random string into the filename tab */

int	ft_dup_filename(t_hdoc *infos, char *buff)
{
	int	j;

	j = 0;
	infos->filename = ft_strdup(buff);
	if (!infos->filename)
	{
		printf("dup filename and buff fail\n");
		return (0);
	}
	while (j < 10)
	{
		if (infos->filename[j] < 0)
			infos->filename[j] *= (-1);
		if (!ft_isalpha((int)infos->filename[j]))
			infos->filename[j] = infos->filename[j] % ('z' - 'a') + 'a';
		j++;
	}
	return (1);
}

/* open the random file and read 10 characters from it. */

int	ft_init_random(t_hdoc *infos)
{
	int		rdmfd;
	char	buff[11];
	int		size;

	rdmfd = open("/dev/random", O_RDONLY);
	if (rdmfd == -1)
	{
		printf("open /random fail\n");
		return (0);
	}
	size = read(rdmfd, buff, 10);
	if (size == -1)
	{
		close(rdmfd);
		printf("read buffer /random fail\n");
		return (0);
	}
	buff[10] = '\0';
	close(rdmfd);
	if (!ft_dup_filename(infos, buff))
		return (0);
	return (1);
}

/* write a random filename and open it */

int	ft_copy_herefile(t_list *line, t_hdoc *infos)
{
	if (!infos->filename)
	{
		if (!ft_init_random(infos))
		{
			free(infos->str);
			free(infos->eof);
			return (0);
		}
	}
	line->fd_hdoc = open(infos->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (line->fd_hdoc == -1)
	{
		free(infos->filename);
		free(infos->str);
		free(infos->eof);
		printf("heredoc fd fail\n");
		return (0);
	}
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
		free(infos->str);
		free(infos->eof);
		printf("reopen hd fail\n");
		return (0);
	}
	return (1);
}

/* This heredoc function resize the keyword by exluding the
 * doubles chevron (<<), create a file with random name,
 * write into this file with readline, stop the writing
 * when the keyword (eof) is written and keep the filename
 * in a double tab to unlink them at the end of the cmd line. */

int	ft_heredoc(t_list *line, t_hdoc *infos, t_env *env, t_data *data)
{
	int	i;

	i = 1;
	while (i <= line->hdoc)
	{
		if (!ft_malloc_strdup_eof(infos, line->redir[i - 1]))
			return (1);
		if (!ft_copy_herefile(line, infos))
			return (1);
		while (1)
		{
			if (!ft_reading_line(infos, env, data))
				return (1);
			if (!ft_strncmp(infos->eof, infos->str, infos->size))
				break ;
			ft_putstr_fd(infos->str, line->fd_hdoc);
			free(infos->str);
		}
		// printf("filename: %s\n", infos->filename);
		ft_init_var(infos, 0);
		i++;
	}
	if (!ft_reopen_hdoc(line, infos))
		return (1);
	return (0);
}
