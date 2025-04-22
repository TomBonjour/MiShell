/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:22:58 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:22:58 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
		return (-1);
	printf("%s\n", path);
	return (0);
}

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i].name != NULL)
	{
		printf("%s=%s\n", env[i].name, env[i].data);
		i++;
	}
	return (0);
}
