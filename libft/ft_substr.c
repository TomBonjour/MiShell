/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 09:42:07 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/25 11:39:12 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*dest;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		dest = ft_strdup("");
		return (dest);
	}
	j = 0;
	if (start + len > ft_strlen(s))
		dest = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
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
