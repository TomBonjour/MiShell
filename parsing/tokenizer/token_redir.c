/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:00 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:01 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_redir_len(char *cmd, int *i)
{
	(*i)++;
	if (ft_is_redir(cmd[*i]) == 1)
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
		{
			if (ft_find_end_quote(cmd, i, cmd[*i]) == -1)
				return (-1);
		}
		(*i)++;
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (0);
}

int	ft_count_redir(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		while (ft_is_redir(cmd[i]) == 0 && cmd[i] != '\0')
		{
			if (ft_is_quote(cmd[i]) == 1)
			{
				if (ft_find_end_quote(cmd, &i, cmd[i]) == -1)
					return (-1);
			}
			i++;
		}
		if (ft_is_redir(cmd[i]) == 1)
		{
			n++;
			i++;
		}
		if (ft_is_redir(cmd[i]) == 1)
			i++;
	}
	return (n);
}

char	*ft_init_malloc_redir(char *cmd, int *i, t_data *data)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (ft_set_error(data, 1));
	str[0] = cmd[*i];
	str[1] = '\0';
	if (ft_is_redir(cmd[++(*i)]) == 1)
	{
		str = ft_realloc_char(str, cmd[*i], data);
		if (data->err == 1)
			return (NULL);
		(*i)++;
	}
	return (str);
}

char	*ft_redir_substr(char *cmd, int *i, t_list **new, t_data *data)
{
	char	*str;

	str = ft_init_malloc_redir(cmd, i, data);
	if (data->err == 1)
		return (NULL);
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
		{
			if (str[0] == '<' && str[1] == '<')
				(*new)->quote_hdoc = 1;
			str = ft_extract_quote(cmd, i, str, data);
		}
		else
			str = ft_extract_str(cmd, i, str, data);
		if (data->err == 1)
			return (NULL);
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (str);
}
