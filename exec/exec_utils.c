/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:21:19 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:21:19 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_builtin_child(t_list *line)
{
	if (ft_find_word(line->args[0], "pwd") == 1)
		line->builtin = 1;
	else if (ft_find_word(line->args[0], "env") == 1)
		line->builtin = 1;
	else if (ft_find_word(line->args[0], "echo") == 1)
		line->builtin = 1;
	if (line->builtin == 1)
		return (1);
	return (0);
}

int	ft_is_builtin_parent(t_list *line)
{
	if (ft_find_word(line->args[0], "exit") == 1)
		line->builtin = 1;
	if (ft_find_word(line->args[0], "cd") == 1)
		line->builtin = 1;
	else if (ft_find_word(line->args[0], "echo") == 1)
		line->builtin = -1;
	else if (ft_find_word(line->args[0], "unset") == 1)
		line->builtin = 1;
	else if (ft_find_word(line->args[0], "export") == 1)
		line->builtin = 1;
	if (line->builtin == 1)
		return (1);
	return (-1);
}

char	*ft_join_equal(char *s1, char *s2, t_data *data)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (ft_set_error(data, 1));
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = '=';
	i++;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_convert_env(t_data *data)
{
	char	**envtab;
	int		i;

	i = 0;
	while (data->env[i].name != NULL)
		i++;
	envtab = malloc(sizeof(char *) * (i + 1));
	if (!envtab)
		return (ft_set_error(data, 1));
	i = 0;
	while (data->env[i].name != NULL)
	{
		envtab[i] = ft_join_equal(data->env[i].name, data->env[i].data, data);
		if (data->err == 1)
			return (NULL);
		i++;
	}
	envtab[i] = NULL;
	return (envtab);
}

int	ft_is_a_directory(char *redir, t_data *data)
{
	if (redir[ft_strlen(redir) - 1] == '/')
	{
		if (redir[1] == '>')
		{
			data->rvalue = 1;
			ft_dprintf(2, "%s : is a directory\n", redir + 2);
			return (-1);
		}
		else
		{
			data->rvalue = 1;
			ft_dprintf(2, "%s : is a directory\n", redir + 1);
			return (-1);
		}
	}
	return (0);
}
