/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_generals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:27:52 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 13:02:25 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_reverse_free(char **tab, int j)
{
	while (j > 0)
	{
		free(tab[j - 1]);
		j--;
	}
	free(tab);
}

void	ft_pathcpy(char str[PATH_MAX], char *src, int size)
{
	int	i;
	
	i = 0;
	while (src[i] != '\0' && i < size)
	{
		str[i] = src[i];
		i++;
	}
}

char	*ft_substr(char *s, int start, int len)
{
	int		j;
	char	*dest;

	if (!s)
		return (0);
	j = 0;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (0);
	while (j < len && s[j + start] != '\0' && start < ft_strlen(s))
	{
		dest[j] = s[j + start];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

// Re-malloc +1 une chaine de caractere et rajoute le char ~c
char	*ft_realloc_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	i++;
	new[i] = '\0';
	free(str);
	return (new);
}


// Extrait une chaine de caractère entre quotes
char	*ft_extract_quote(char *cmd, int *i, char *str, char quote)
{
	if (quote == '\0')
		quote = cmd[*i];
	str = ft_realloc_char(str, cmd[*i]);
	if (!str)
		return (NULL);
	(*i)++;
	while (cmd[*i] != quote)
	{
		str = ft_realloc_char(str, cmd[*i]);
		if (!str)
			return (NULL);
		(*i)++;
	}
	str = ft_realloc_char(str, cmd[*i]);
	if (!str)
		return (NULL);
	(*i)++;
	return (str);
}

// Extrait un argument entier
char	*ft_extract_str(char *cmd, int *i, char *str)
{
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0
		&& cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, cmd[*i]);
		else
		{
			str = ft_realloc_char(str, cmd[*i]);
			if (!str)
				return (NULL);
			(*i)++;
		}
	}
	return (str);
}

int	ft_is_blank(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

int	ft_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else
		return (0);
}
