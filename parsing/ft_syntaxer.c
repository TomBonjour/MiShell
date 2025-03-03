/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntaxer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:38:09 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/03 20:04:55 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_syntaxer(t_list *line)
{
	int	i;

	while (line != NULL)
	{
		i = 0;
		if (line->args[0] == NULL && line->redir[0] == NULL)
			return (-1);
		i = 0;
		while (line->redir[i] != NULL)
		{
			if (ft_check_redir_syntax(line->redir[i]) == -1)
				return (-1);
			i++;
		}
		line = line->next;
	}
	return (0);
}
