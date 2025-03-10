/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:34:38 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 12:46:29 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


// ECHO-2 : Regarde si un argument de echo est une option -n
// 		
int	ft_is_option(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			else
				i++;
		}
		return (1);
	}
	return (0);
}


// COMMANDE ECHO
// 		Regarde si le 1er arg de echo, puis les suivants sont des -n avec ECHO-2
//		Print les arguments séparés par un espace, puis \n si il n'y a pas d'option
void	ft_echo(char **tab)
{
	int	i;
	int	opt;
	int	size;

	i = 1;
	size = 0;
	while (tab[size] != NULL)
		size++;
	opt = ft_is_option(tab[1]);
	if (opt == 1)
	{
		i = 2;
		while (ft_is_option(tab[i]) == 1)
			i++;
	}
	while (tab[i] != NULL)
	{
		printf("%s", tab[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	if (opt == 0)
		printf("\n");
}

// + ft_exit
