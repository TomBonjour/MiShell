/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_white.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:55:55 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 14:37:27 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	reverse_free(char **tab, int j)
{
	while (j > 0)
	{
		free(tab[j - 1]);
		j--;
	}
	free(tab);
}

char	**ft_fill_line_white(char **tab, char *s, int j, int len)
{
	int	k;

	k = 0;
	while (k < len)
	{
		tab[j][k] = s[k];
		k++;
	}
	tab[j][k] = '\0';
	return (tab);
}

static char	**ft_fill_tab(char *s, char **tab, char c, int j)
{
	int		len;

	while (*s != '\0')
	{
		while ((*s == c || (*s >= '\b' && *s <= '\r')) && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		len = 0;
		while ((s[len] != c || (s[len] >= '\b' && s[len] <= '\r'))
			&& s[len] != '\0')
			len ++;
		tab[j] = malloc(sizeof(char) * (len + 1));
		if (!tab[j])
		{
			reverse_free(tab, j);
			return (NULL);
		}
		ft_fill_line_white(tab, s, j, len);
		s += len;
		j++;
	}
	tab[j] = NULL;
	return (tab);
}

static int	count_words(char const *s, char c)
{
	size_t	i;
	int		n;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == c || (s[i] >= '\b' && s[i] <= '\r')) && s[i] != '\0')
			i++;
		if (s[i] != '\0')
			n++;
		while ((s[i] != c && (s[i] <= '\b' || s[i] >= '\r')) && s[i] != '\0')
			i++;
	}
	return (n);
}

char	**ft_split_white(char const *s, char c)
{
	int		size;
	char	**tab;
	int		j;

	j = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
	{
		tab = malloc(sizeof(char *) * 2);
		if (!tab)
			return (NULL);
		tab[0] = ft_strdup("");
		tab[1] = NULL;
		return (tab);
	}
	size = count_words(s, c);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (NULL);
	tab = ft_fill_tab((char *)s, tab, c, j);
	if (!tab)
		return (NULL);
	return (tab);
}
