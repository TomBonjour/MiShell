#include "../../minishell.h"

void	ft_syntax_error(t_list **line, t_data *data)
{
	printf("syntax error\n");
	data->rvalue = 2;
	data->err = 0;
	ft_free_list(line);
}

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

char	*ft_send_to_expand(t_list *line, char *str, t_env *env, t_data *data)
{
	if (ft_need_to_expand(str) == 1)
	{
		str = ft_expander(str, env, data);
		if (data->err == 1)
			ft_free_and_exit(line, env);
	}
	return (str);
}

void	*ft_syntax_and_expand(t_list *line, t_env *env, t_data *data)
{
	int	i;

	while (line != NULL)
	{
		if (line->args[0] == NULL && line->redir[0] == NULL)
			return (ft_set_error(data, 2));
		i = 0;
		while (line->args[i])
		{
			line->args[i] = ft_send_to_expand(line, line->args[i], env, data);
			i++;
		}
		i = 0;
		while (line->redir[i])
		{
			if (ft_check_redir_syntax(line->redir[i]) == -1)
				return (ft_set_error(data, 2));
			line->redir[i] = ft_send_to_expand(line, line->redir[i], env, data);
			i++;
		}
		line = line->next;
	}
	return (0);
}
