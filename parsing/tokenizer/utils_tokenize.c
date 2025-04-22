#include "../../minishell.h"

int	ft_count_args(char *cmd, int i)
{
	int	n;

	n = 0;
	while (cmd[i] != '\0')
	{
		while (ft_is_redir(cmd[i]) == 1)
		{
			if (ft_redir_len(cmd, &i) == -1)
				return (-1);
		}
		if (cmd[i] != '\0')
			n++;
		while (ft_is_blank(cmd[i]) == 0 && ft_is_redir(cmd[i]) == 0 && cmd[i])
		{
			if (ft_is_quote(cmd[i]) == 1)
			{
				if (ft_find_end_quote(cmd, &i, cmd[i]) == -1)
					return (-1);
			}
			i++;
		}
		while (ft_is_blank(cmd[i]) == 1 && cmd[i] != '\0')
			i++;
	}
	return (n);
}

char	*ft_arg_substr(char *cmd, int *i, t_data *data)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (!str)
		return (ft_set_error(data, 1));
	str[0] = '\0';
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, data);
		else
			str = ft_extract_str(cmd, i, str, data);
		if (data->err == 1)
			return (NULL);
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (str);
}

int	ft_count_nodes(t_list *line)
{
	int		n;
	t_list	*temp;

	n = 0;
	temp = line;
	while (line != NULL)
	{
		line = line->next;
		n++;
	}
	line = temp;
	return (n);
}

int	ft_skip_all_quotes(char **s, int *len)
{
	while (ft_is_blank(**s) == 1)
		*s += 1;
	*len = 0;
	while ((*s)[*len] != '|' && s[0][*len] != '\0')
	{
		if (ft_is_quote((*s)[*len]) == 1)
			if (ft_find_end_quote(*s, len, (*s)[*len]) == -1)
				return (-1);
		(*len)++;
	}
	return (*len);
}

void	ft_end_of_get_cmd(t_list **new, int *j, int *k, t_data *data)
{
	if ((*new)->nb_redir > 0)
	{
		(*new)->last_infile = ft_last_infile(*new, (*new)->nb_redir);
		(*new)->redir = ft_hdoc_prio((*new)->redir,
				(*new)->nb_redir, new, data);
	}
	(*new)->redir[++(*j)] = NULL;
	(*new)->args[++(*k)] = NULL;
}
