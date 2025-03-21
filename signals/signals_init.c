#include "../minishell.h"

void	ft_init_var(t_heredoc *infos, int *idoc, int flag)
{
	if (flag == 1)
	{
		infos->fd = 0;
		infos->size = 0;
		infos->str = NULL;
		infos->eof = NULL;
		infos->filename = NULL;
		*idoc = 0;
	}
	else
	{
		unlink(infos->filename);
		free(infos->str);
		free(infos->eof);
		free(infos->filename);
		close(infos->fd);
	}
}
