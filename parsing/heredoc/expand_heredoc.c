/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:21 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:21 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_expand_heredoc(char *str, t_data *data)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '$' && str[i] != '\0')
			i++;
		if (str[i] == '$'
			&& ft_is_heredoc_xpendable(str[i + 1]) == 1)
		{
			if (str[i + 1] == '?')
				str = ft_expand_quest_mark(str, i, data);
			else
				str = ft_expand_env_var(str, &i, data);
			if (data->err == 1)
				return (NULL);
		}
		if (str[i] != '\0')
			i++;
	}
	return (str);
}
