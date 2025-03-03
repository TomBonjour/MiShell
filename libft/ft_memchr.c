/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:52:05 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/29 16:10:10 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *memory, int c, size_t n)
{
	size_t			i;
	unsigned char	*m;

	m = (unsigned char *)memory;
	c = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (m[i] == c)
			return (&m[i]);
		i++;
	}
	return (NULL);
}
