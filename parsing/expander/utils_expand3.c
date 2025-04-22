/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:30 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:30 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**ft_split_join(char **split, char **tab, int n, t_data *data)
{
	if (tab[n][0] != '$')
	{
		split = ft_join_content_before(split, tab[n], data);
		if (data->err == 1)
			return (ft_set_error(data, 1));
	}
	return (split);
}

void	ft_init_remove_quotes(int *i, int *j, int *nb_quote)
{
	*i = 0;
	*j = 0;
	*nb_quote = 1;
}

char	*ft_realloc_quote_protection(char *str, int pos, t_data *data)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2 + 1));
	if (!new)
		return (ft_set_error(data, 1));
	while (i < pos)
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = '"';
	new[i++] = str[pos++];
	new[i++] = '"';
	while (str[pos] != '\0')
	{
		new[i] = str[pos];
		i++;
		pos++;
	}
	new[i] = '\0';
	free(str);
	return (new);
}

char	**ft_quote_protection(char **split, t_data *data)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (split[i] != NULL)
	{
		j = 0;
		while (split[i][j] != '\0')
		{
			if (split[i][j] == '\'' || split[i][j] == '"')
			{
				split[i] = ft_realloc_quote_protection(split[i], j, data);
				if (data->err == 1)
					return (NULL);
				j += 2;
			}
			j++;
		}
		i++;
	}
	return (split);
}
