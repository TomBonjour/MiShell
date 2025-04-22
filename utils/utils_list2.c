/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:01 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:18:03 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <minishell.h>

int	ft_copy_env_name(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '=')
		(*i)++;
	env[j].name = malloc(sizeof(char) * (*i + 1));
	if (!env[j].name)
		return (-1);
	env[j].name[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].name[*i] = envp[j][*i];
		(*i)--;
	}
	return (0);
}

int	ft_copy_env_data(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '\0')
		(*i)++;
	(*i) -= ft_strlen(env[j].name) + 1;
	env[j].data = malloc(sizeof(char) * (*i + 1));
	if (!env[j].data)
		return (-1);
	env[j].data[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].data[*i] = envp[j][*i + ft_strlen(env[j].name) + 1];
		(*i)--;
	}
	return (0);
}

int	ft_copy_name_data(char **envp, t_env *env, int j, int *i)
{
	if (ft_copy_env_name(envp, env, j, i) == -1)
		return (-1);
	*i = ft_strlen(env[j].name) + 2;
	if (ft_copy_env_data(envp, env, j, i) == -1)
		return (-1);
	return (0);
}

void	ft_init_env_name_data(t_env *env, int j)
{
	while (j >= 0)
	{
		env[j].name = NULL;
		env[j].data = NULL;
		j--;
	}
}

t_env	*ft_set_env(char **envp, t_data *data)
{
	t_env	*env;
	int		i;
	int		j;

	j = 0;
	while (envp[j] != NULL)
		j++;
	env = malloc(sizeof(t_env) * (j + 1));
	if (!env)
		return (ft_set_error(data, 1));
	ft_init_env_name_data(env, j);
	j = 0;
	while (envp[j] != NULL)
	{
		i = 0;
		if (ft_copy_name_data(envp, env, j, &i) == -1)
		{
			ft_set_error(data, 1);
			return (env);
		}
		j++;
	}
	env[j].name = NULL;
	env[j].data = NULL;
	return (env);
}
