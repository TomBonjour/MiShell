/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:24:40 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/03 20:00:56 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Calcule la taille d'une redirection
// --> Utilisée pour skip la redirection quand on compte les arguments non-redir
void	ft_redir_len(char *cmd, int *i)
{
	(*i)++;
	if (ft_is_redir(cmd[*i]) == 1)
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			ft_find_end_quote(cmd, i, cmd[*i]);
		(*i)++;
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
}

// Compte le nombre de redirections dans la string
// --> Utilisée pour malloc le tableau de redir
int	ft_count_redir(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		while (ft_is_redir(cmd[i]) == 0 && cmd[i] != '\0')
		{
			if (ft_is_quote(cmd[i]) == 1)
				ft_find_end_quote(cmd, &i, cmd[i]);
			i++;
		}
		if (ft_is_redir(cmd[i]) == 1)
		{
			n++;
			i++;
		}
		if (ft_is_redir(cmd[i]) == 1)
			i++;
	}
	return (n);
}

// Compte le nombre d'arguments non-redir dans la string
// --> Utilisée pour malloc le tableau de commande/arguments
int	ft_count_args(char *cmd)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (cmd[i] != '\0')
	{
		while (ft_is_redir(cmd[i]) == 1)
			ft_redir_len(cmd, &i);
		if (cmd[i] != '\0')
			n++;
		while (ft_is_blank(cmd[i]) == 0 && ft_is_redir(cmd[i]) == 0 && cmd[i])
		{
			if (ft_is_quote(cmd[i]) == 1)
				ft_find_end_quote(cmd, &i, cmd[i]);
			i++;
		}
		while (ft_is_blank(cmd[i]) == 1 && cmd[i] != '\0')
			i++;
	}
	return (n);
}

// Extrait la redirection dans une string malloquée en format ">xxxxx"
// --> Utilisée pour remplir le tableau de redir
char	*ft_redir_substr(char *cmd, int *i)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL);
	str[0] = cmd[*i];
	str[1] = '\0';
	(*i)++;
	if (ft_is_redir(cmd[*i]) == 1)
	{
		str = ft_realloc_char(str, cmd[*i]);
		if (!str)
			return (NULL);
		(*i)++;
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, cmd[*i]);
		else
			str = ft_extract_str(cmd, i, str);
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (str);
}

// Extrait l'argument dans une string malloquée en format "xxxx"
// --> Utilisée pour remplir le tableau de commande/arguments
char	*ft_arg_substr(char *cmd, int *i)
{
	char	*str;
	char	quote;

	quote = '\0';
	str = malloc(sizeof(char) * 1);
	if (!str)
		return (NULL);
	str[0] = '\0';
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
		{
			quote = cmd[*i];
			str = ft_extract_quote(cmd, i, str, quote);
		}
		else
			str = ft_extract_str(cmd, i, str);
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (str);
}
