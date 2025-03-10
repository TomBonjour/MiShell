/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:56:13 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 12:51:44 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// A FINIR !!! Free la list et exit le programme en affichant syntax_error
void	ft_syntax_error(t_list **args, char *mess)
{
	if (args == NULL)
		(void)args;
	if (mess == NULL)
		(void)mess;
	printf("Syntax error\n");
	exit (0);
}

// Trouve la fin de la quote dans laquelle on est entré.
// Renvoie syntax error si la quote n'a pas de fin.
// 		Utilisée dès qu'on trouve une quote et qu'on veut la passer
void	ft_find_end_quote(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	if (s[*i] == '\0')
		ft_syntax_error(NULL, "missing quote");
}

/*void	ft_remove_quote(t_list *line)
{
	
}*/
