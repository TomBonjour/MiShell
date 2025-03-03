/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 14:29:41 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/25 15:36:50 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start_trim_str(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = -1;
	while (s1[i] != '\0' && start == -1)
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
			}
			else
				j++;
		}
		start = i;
	}
	return (start);
}

static int	end_trim_str(const char *s1, const char *set)
{
	int	i;
	int	j;
	int	end;

	i = ft_strlen(s1) - 1;
	j = 0;
	end = -1;
	while (i > 0 && end == -1)
	{
		while (set[j] != '\0')
		{
			if (s1[i] == set[j])
			{
				i--;
				j = 0;
			}
			else
				j++;
		}
		end = i;
	}
	return (end);
}

static char	*trim_strdup(const char *s1, int len, int startword, int endword)
{
	int		i;
	int		j;
	char	*str;

	i = startword;
	j = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	while (i <= endword)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*str;
	int		startword;
	int		endword;
	int		len;

	if (!s1 || !set)
		return (0);
	if (s1[0] == '\0')
	{
		str = ft_strdup("");
		return (str);
	}
	startword = start_trim_str(s1, set);
	endword = end_trim_str(s1, set);
	if (startword + (ft_strlen(s1) - endword - 1) > ft_strlen(s1))
	{
		str = ft_strdup("");
		return (str);
	}
	len = ft_strlen(s1) - startword - (ft_strlen(s1) - endword - 1);
	str = trim_strdup(s1, len, startword, endword);
	return (str);
}
