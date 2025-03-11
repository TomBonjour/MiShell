/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_exp_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 21:38:10 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/10 15:13:25 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// COMMANDE ENV : imprime la copie du tableau de variables d'environnement
int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i].name != NULL)
	{
		printf("%s", env[i].name);
		printf("=");
		printf("%s\n", env[i].data);
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
