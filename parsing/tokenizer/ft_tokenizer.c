/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:08 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:09 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_malloc_arrays(char *cmd, t_list **new, t_data *data)
{
	int	i;

	i = 0;
	(*new)->nb_args = ft_count_args(cmd, i);
	if ((*new)->nb_args == -1)
		return (ft_set_error(data, 2));
	(*new)->nb_redir = ft_count_redir(cmd);
	if ((*new)->nb_redir == -1)
		return (ft_set_error(data, 2));
	(*new)->args = malloc(sizeof(char *) * ((*new)->nb_args + 1));
	(*new)->redir = malloc(sizeof(char *) * ((*new)->nb_redir + 1));
	(*new)->quote = malloc(sizeof(int) * ((*new)->nb_redir));
	if (!(*new)->args || !(*new)->redir || !(*new)->quote)
		return (ft_set_error(data, 1));
	(*new)->args[0] = NULL;
	(*new)->redir[0] = NULL;
	return (0);
}

void	*ft_get_cmd_and_redir(char *cmd, int i, t_list **new, t_data *data)
{
	int	j;
	int	k;

	j = -1;
	k = -1;
	if (ft_malloc_arrays(cmd, new, data) == NULL && data->err != 0)
		return (NULL);
	while (cmd[i] != '\0')
	{
		if (ft_is_redir(cmd[i]) == 1)
		{
			(*new)->redir[++j] = ft_redir_substr(cmd, &i, new, data);
			if ((*new)->quote_hdoc == 1)
				(*new)->quote[j] = 1;
			else
				(*new)->quote[j] = 0;
			(*new)->quote_hdoc = 0;
		}
		else
			(*new)->args[++k] = ft_arg_substr(cmd, &i, data);
		if (data->err == 1)
			return (NULL);
	}
	ft_end_of_get_cmd(new, &j, &k, data);
	return (0);
}

t_list	**ft_new_add_back(char *s, int len, t_list **args, t_data *data)
{
	t_list	*new_arg;
	char	*cmd;

	if (len > 0)
	{
		while (ft_is_blank(s[len - 1]) == 1 && len > 0)
			len--;
	}
	cmd = ft_substr(s, 0, len);
	if (!cmd)
		return (ft_set_error(data, 1));
	new_arg = ft_lst_new_node(cmd, data);
	free(cmd);
	ft_lstadd_back(args, new_arg);
	return (args);
}

t_list	*ft_split_line(char *s, t_list *args, int len, t_data *data)
{
	while (*s != '\0')
	{
		if (ft_skip_all_quotes(&s, &len) == -1)
			return (ft_set_error(data, 2));
		if (s[len] == '\0')
		{
			if (ft_new_add_back(s, len, &args, data) == NULL && data->err == 1)
				return (args);
			return (args);
		}
		if (s[len] == '|')
		{
			if (ft_new_add_back(s, len, &args, data) == NULL && data->err == 1)
				return (args);
			s += len;
			if (s[1] == '\0')
			{
				ft_free_list(&args);
				return (ft_set_error(data, 2));
			}
		}
		s++;
	}
	return (args);
}

t_list	*ft_tokenize(char *s, t_data *data)
{
	t_list	*line;
	int		len;

	if (s == NULL)
		return (NULL);
	len = 0;
	line = NULL;
	while (ft_is_blank(*s) == 1)
		s++;
	if (*s == '\0')
		return (NULL);
	line = ft_split_line(s, line, len, data);
	if (data->err == 1)
		return (line);
	else if (!line)
		return (NULL);
	data->nodes = ft_count_nodes(line);
	return (line);
}
