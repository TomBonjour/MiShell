/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenize.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:21:36 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/03 20:00:22 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Compte le nombre d'arguments et de redirections dans la commande, malloc
// Parcoure la string et envoie la position a ft_arg_substr() si il trouve
// un argument et a ft_redir_substr() si il trouve une redirection
// 	Remplit les tableaux avec les sub-string renvoyées par ces fonctions

int	ft_get_command_and_redir(char *cmd, t_list **new_elem)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	k = -1;
	(*new_elem)->args = malloc(sizeof(char *) * (ft_count_args(cmd) + 1));
	(*new_elem)->redir = malloc(sizeof(char *) * (ft_count_redir(cmd) + 1));
	if (!(*new_elem)->args || !(*new_elem)->redir)
		return (-1);
	while (cmd[i] != '\0')
	{
		if (ft_is_redir(cmd[i]) == 1)
			(*new_elem)->redir[++j] = ft_redir_substr(cmd, &i);
		else
			(*new_elem)->args[++k] = ft_arg_substr(cmd, &i);
	}
	k++;
	j++;
	(*new_elem)->args[k] = NULL;
	(*new_elem)->redir[j] = NULL;
	return (0);
}

// 3. Tronque les espaces restant de la commande
// 		Envoie la string a lst_new() pour créer le nouveau node
// 		Envoie le nouveau node a lst_add_back() l'ajouter a la liste existante
t_list	**ft_lst_new_add_back(char *s, int len, t_list **args)
{
	t_list	*new_arg;
	char	*cmd;

	while (ft_is_blank(s[len - 1]) == 1 && len > 0)
		len--;
	cmd = ft_substr(s, 0, len);
	new_arg = ft_lstnew(cmd);
	if (new_arg == 0)
		return (NULL);
	free(cmd);
	ft_lstadd_back(args, new_arg);
	return (args);
}

// 2. Enleve les blank et split par les pipes
// 		Envoie chaque partie a lst_new_add_back(3) pour créer la liste chainee
t_list	*ft_split_line(char *s, t_list *args)
{
	int		len;
	int		quote;

	quote = 0;
	while (ft_is_blank(*s) == 1)
			s++;
		if (*s == '\0')
			return (NULL);
	while (*s != '\0')
	{
		while (ft_is_blank(*s) == 1)
			s++;
		len = 0;
		while (s[len] != '|' && s[len] != '\0')
		{
			if (ft_is_quote(s[len]) == 1)
				ft_find_end_quote(s, &len, s[len]);
			len++;
		}
		if (s[len] == '\0')
		{
			ft_lst_new_add_back(s, len, &args);
			return (args);
		}
		if (s[len] == '|')
		{
			ft_lst_new_add_back(s, len, &args);
			s += len;
		}
		s++;
	}
	return (args);
}

//1. Split (|) l'input en commandes avec split_line(2)

t_list	*ft_tokenize(char *input)
{
	t_list	*line;

	line = NULL;
	if (input == NULL)
		return (NULL);
	line = ft_split_line(input, line);
	if (ft_syntaxer(line) == -1)
		ft_syntax_error(&line, NULL);
	if (!line)
		return (NULL);
	return (line);
}

//PROCHAINES ETAPES : remove quote
