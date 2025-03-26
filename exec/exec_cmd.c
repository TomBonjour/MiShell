#include "../minishell.h"

int	ft_exec_cmd(t_list *line, t_env *env, t_data *data)
{
	t_hdoc infos;

	if (ft_pars_env(env, data))
		return (1);
	while (line != NULL)
	{
		if (line->hdoc != 0)
		{
			ft_init_var(&infos, 1);
			ft_heredoc(line, &infos, env, data);
		}
		if (ft_test_path(line))
			ft_fill_pathnames(data, line);
		// TODO exec pipex ICI
		line = line->next;
	}
	return (0);
}
