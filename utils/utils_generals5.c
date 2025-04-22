/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generals5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:14 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:18:15 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../minishell.h>

char	**ft_join_content_before(char **split, char *str, t_data *data)
{
	char	*join;
	char	*before;
	int		size;
	int		i;

	size = 0;
	i = -1;
	while (str[size] != '$')
		size++;
	before = malloc(sizeof(char) * (size + 1));
	if (!before)
		return (ft_set_error(data, 1));
	while (str[++i] != '$')
		before[i] = str[i];
	before[i] = '\0';
	join = ft_strjoin(before, split[0]);
	free(before);
	if (!join)
		return (ft_set_error(data, 1));
	free(split[0]);
	split[0] = ft_strdup(join);
	free(join);
	if (!split[0])
		return (ft_set_error(data, 1));
	return (split);
}

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len] != NULL)
		len++;
	return (len);
}

int	ft_quote_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\'' && str[i] != '"' && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		return (1);
	return (0);
}
