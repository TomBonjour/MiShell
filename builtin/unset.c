/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:20:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/03/12 15:41:42 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*ft_realloc_env(int i, t_env *env)
{
	t_env 	*new;

	if (!i || !env)
		return (NULL);
	new = malloc(sizeof(t_env) * (i + 1));
	if (!new)
		return (NULL);
	return (new);
}

int 	ft_unset_find_var(char *var, t_env *env)
{
	int	i;
	int	size;

	i = 0;
	while (env[i].name != NULL)
	{
		size = ft_strlen(env[i].name);
		if (!ft_strncmp(var, env[i].name, size))
			return (0);
		i++;
	}
	return (1);
}

void	ft_unset_fill_env(t_env *new, char *var, t_env *env, int i)
{
	int	j;
	int	k;
	int	size;

	j = 0;
	k = 0;
	while (j < i)
	{
		size = ft_strlen(env[j].name);
		if (!ft_strncmp(var, env[k].name, size))
			k++;
		new[j].name = env[k].name;
		new[j].data = env[k].data;
		k++;
		j++;
	}
	new[j].name = NULL;
	new[j].data = NULL;
}

t_env	*ft_unset(char *var, t_env *env)
{
	int		i;
	t_env	*new;

	i = 0;
	if (ft_unset_find_var(var, env))
		return (env);
	while (env[i].name != NULL)
		i++;
	new = ft_realloc_env(i - 1, env);
	if (!new)
		return (0);
	ft_unset_fill_env(new, var, env, i - 1);
	return (new);
}
