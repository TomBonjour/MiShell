#include "../minishell.h"

int	ft_exec_cmd(t_list *line, t_env *env, t_data *data)
{
	if (ft_pars_env(env, data))
		return (1);
	while (line != NULL)
	{
		// TODO verifier le heredoc ICI
		if (ft_test_path(line))
			ft_fill_pathnames(data, line);
		// TODO exec pipex ICI
		line = line->next;
	}
	return (0);
}
