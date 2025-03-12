#include "../minishell.h"


// 
int	ft_check_redir_syntax(char *redir)
{
	if (ft_is_redir(redir[1]) == 1)
	{
		if (redir[0] != redir[1] || redir[2] == '\0')
			return (-1);
	}
	else
	{
		if (redir[1] == '\0')
			return (-1);
	}
	return (0);
}

int	ft_syntax_and_expand(t_list *line, t_env *env)
{
	int	i;

	while (line != NULL)
	{
		if (line->args[0] == NULL && line->redir[0] == NULL)
			return (-1);
		i = 0;
		while (line->args[i])
		{
			ft_expander(line->args[i], env);
			i++;
		}
		i = 0;
		while (line->redir[i])
		{
			if (ft_check_redir_syntax(line->redir[i]) == -1)
				return (-1);
			ft_expander(line->redir[i], env);
			i++;
		}
		line = line->next;
	}
	return (0);
}
