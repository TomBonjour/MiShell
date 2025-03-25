#include "../../minishell.h"

/* resize the keyword by exluding the doubles chevron (<<).*/

int	ft_malloc_strdup_eof(t_hdoc *infos, t_list *line)
{
	static int	i = -1;

	i += 1;
	infos->eof = ft_strjoin(line->redir[i] + 2, "\n");
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

int	ft_dup_filename(t_hdoc *infos, char *buff, int *i)
{
	int	j;

	j = 0;
	infos->filename[*i] = ft_strdup(buff);
	if (!infos->filename[*i])
	{
		printf("dup filename and buff fail\n");
		return (0);
	}
	while (j < 10)
	{
		if (infos->filename[*i][j] < 0)
			infos->filename[*i][j] *= (-1);
		if (!ft_isalpha((int)infos->filename[*i][j]))
			infos->filename[*i][j] = infos->filename[*i][j] % ('z' - 'a') + 'a';
		j++;
	}
	return (1);
}

/* open the random file and read 10 characters from it. */

int	ft_init_random(t_hdoc *infos, int *i)
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
	if (!ft_dup_filename(infos, buff, i))
		return (0);
	return (1);
}

/* write a random filename and open it */

int	ft_copy_herefile(t_hdoc *infos)
{
	static int	i;

	i = 0;
	if (!ft_init_random(infos, &i))
	{
		free(infos->str);
		free(infos->eof);
		return (0);
	}
	infos->fd = open(infos->filename[i], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (infos->fd == -1)
	{
		free(infos->filename);
		free(infos->str);
		free(infos->eof);
		printf("heredoc fd fail\n");
		return (0);
	}
	i++;
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
	while (i <= data->hdoc)
	{
		if (ft_malloc_strdup_eof(infos, line))
			return (1);
		if (!ft_copy_herefile(infos))
			return (1);
		while (1)
		{
			if (!ft_reading_line(infos, env, data))
				return (1);
			if (!ft_strncmp(infos->eof, infos->str, infos->size))
				break ;
			ft_putstr_fd(infos->str, infos->fd);
			free(infos->str);
		}
		printf("filename: %s\n", infos->filename[0]);
		ft_init_var(infos, 0);
		i++;
	}
	return (0);
}
