/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:11:45 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/29 16:09:57 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	n;

	n = 0;
	while (str[n] != '\0')
	{
		n++;
	}
	i = n;
	if ((char)c == 0)
		return ((char *)&str[i]);
	while (i > 0)
	{
		if (str[i - 1] == (char)c)
			return ((char *)&str[i - 1]);
		i--;
	}
	return (NULL);
}
