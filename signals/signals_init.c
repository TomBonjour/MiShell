#include "../minishell.h"

/* initialising all the data I need in the heredoc to NULL/0,
 * so I can send them into my functions without problems.
 * If the flag is different than 1, this function close the fd
 * and free the data I malloc before, exept for the filename.
 * It will be free at the end of the entire cmd line. */

void	ft_init_var(t_hdoc *infos, int flag)
{
	if (flag == 1)
	{
		infos->size = 0;
		infos->str = NULL;
		infos->eof = NULL;
		infos->filename = NULL;
	}
	else
	{
		free(infos->str);
		free(infos->eof);
	}
}
