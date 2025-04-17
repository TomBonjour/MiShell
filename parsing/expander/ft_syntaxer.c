#include "../../minishell.h"

void	ft_syntax_error(t_list **line, t_data *data)
{
	ft_dprintf(2, "syntax error\n");
	data->rvalue = 2;
	data->err = 0;
	ft_free_list(line);
}

char	**ft_suppress_empty_arg(char **tab, int i)
{
	char	**new;
	int		j;

	j = 0;
	new = malloc(sizeof (char *) * ft_tablen(tab) - 1 + 1);
	while (j < i)
	{
		new[j] = ft_strdup(tab[j]);
		j++;
	}
	i++;
	while (tab[i] != NULL)
		new[j++] = ft_strdup(tab[i++]);
	new[j] = NULL;
	i = 0;
	ft_free_tab(tab, 0);
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

void	*ft_syntax_and_expand_redir(t_list *line, t_data *data)
{
	int	i;

	i = 0;
	while (line->redir[i])
	{
		if (ft_check_redir_syntax(line->redir[i]) == -1)
			return (ft_set_error(data, 2));
		if (ft_need_to_expand(line->redir[i]) == 1)
			line->redir = ft_expander(line->redir, i, data);
		if (data->err == 1 || line->redir == NULL)
			return (NULL);
		i++;
	}
	return (line);
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
			if (ft_need_to_expand(line->args[i]) == 1)
				line->args = ft_expander(line->args, i, data);
			if (data->err == 1 || line->args == NULL)
				return (NULL);
			if (!line->args[i])
				break ;
			i++;
		}
		if (ft_syntax_and_expand_redir(line, data) == NULL)
			return (NULL);
		line = line->next;
	}
	return (0);
}
