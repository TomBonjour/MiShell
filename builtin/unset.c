/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:20:17 by jnauroy           #+#    #+#             */
/*   Updated: 2025/03/19 13:36:46 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_find_equal(char *var)
{
	int	numequal;
	int	i;

	i = 0;
	numequal = 0;
	while (var[i] != '\0')
	{
		if (var[i] == '=')
			numequal++;
		i++;
	}
	if (numequal == 0)
		return (1);
	return (0);
}

t_env	*ft_realloc_env(int i)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * (i + 1));
	if (!new)
		return (NULL);
	new[i].name = NULL;
	new[i].data = NULL;
	return (new);
}

int	ft_unset_find_var(char *var, t_env *env)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = ft_strlen(var);
	while (env[i].name != NULL)
	{
		if (size == ft_strlen(env[i].name))
		{
			j = 0;
			while (var[j] == env[i].name[j]
				&& (j < size || env[i].name[j] != '\0'))
				j++;
			if (!ft_strncmp(var, env[i].name, size))
				return (0);
		}
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
		size = ft_strlen(env[k].name);
		if (!ft_strncmp(var, env[k].name, size))
		{
			free(env[k].name);
			free(env[k].data);
			k++;
		}
		new[j] = env[k];
		j++;
		k++;
	}
}

t_env	*ft_unset(char **argv, t_env *env)
{
	int		i;
	int		j;
	t_env	*new;

	j = 1;
	while (argv[j])
	{
		i = 0;
		if (!ft_unset_find_var(argv[j], env))
		{
			while (env[i].name != NULL)
				i++;
			new = ft_realloc_env(i - 1);
			if (!new)
				return (0);
			ft_unset_fill_env(new, argv[j], env, i - 1);
			free(env);
			env = new;
		}
		j++;
	}
	return (env);
}
