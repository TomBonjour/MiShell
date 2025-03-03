/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 20:06:39 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/25 13:58:45 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *to_find, size_t n)
{
	size_t			i;
	size_t			j;
	unsigned char	*s;
	unsigned char	*tf;

	if (!src && n == 0)
		return (0);
	s = (unsigned char *)src;
	tf = (unsigned char *)to_find;
	i = 0;
	j = 0;
	if (ft_strlen((const char *)s) < ft_strlen((const char *)tf))
		return (0);
	if (tf[0] == '\0')
		return ((char *)s);
	while (s[i] != '\0')
	{
		j = 0;
		while (s[i + j] == tf[j] && i + j < n && s[i + j])
			j++;
		if (tf[j] == '\0')
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
