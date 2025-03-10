/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:38:10 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 12:36:33 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// COMMANDE ENV : imprime la copie du tableau de variables d'environnement
int	ft_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !env[i])
		return (-1);
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

/*int	ft_export(char **tab, t_env *env)
{

}


int	ft_unset(char **tab, t_env *env)
{

}*/
