#include "../../minishell.h"

void	ft_syntax_error(t_list **line, t_data *data)
{
	ft_dprintf(2, "syntax error\n");
	data->rvalue = 2;
	data->err = 0;
	ft_free_list(line);
}

char	**ft_suppress_empty_arg(t_list *line, char **tab, int i)
{
	char	**new;
	int		j;

	j = 0;
	new = malloc(sizeof (char *) * line->nb_args - 1 + 1);
	while (j < i)
	{
		new[j] = ft_strdup(tab[j]);
		j++;
	}
	i++;
	while (tab[i] != NULL)
		new[j++] = ft_strdup(tab[i++]);
	new[j] = NULL;
	ft_free_tab(tab);
	return (new);
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

char	*ft_send_to_expand(char *str, t_data *data)
{
	if (ft_need_to_expand(str) == 1)
	{
		str = ft_expander(str, data);
		if (data->err == 1)
			return (NULL);
	}
	return (str);
}

void	*ft_syntax_and_expand(t_list *line, t_data *data)
{
	int	i;

	while (line != NULL)
	{
		if (line->args[0] == NULL && line->redir[0] == NULL)
			return (ft_set_error(data, 2));
		i = 0;
		while (line->args[i])
		{
			line->args[i] = ft_send_to_expand(line->args[i], data);
			if (line->args[i][0] == '\0')
				line->args = ft_suppress_empty_arg(line, line->args, i);
			else
				i++;
		}
		i = 0;
		while (line->redir[i])
		{
			line->redir[i] = ft_send_to_expand(line->redir[i], data);
			if (ft_check_redir_syntax(line->redir[i]) == -1)
				return (ft_set_error(data, 2));
			i++;
		}
		line = line->next;
	}
	return (0);
}
