#include "../minishell.h"

void	ft_open_infile(t_list *line, t_data *data)
{
	int 	i;

	i = 0;
	while (line->redir[i] != NULL)
	{
		if (line->fd_infile != 0)
			close(line->fd_infile);
		if (line->redir[i][0] == '<')
		{
			line->fd_infile = open(line->redir[i + 1], O_RDONLY);
			if (line->inf == -1)
				printf("error\n"); //erreur No such file or directory;
		}
		i++;
	}
}
