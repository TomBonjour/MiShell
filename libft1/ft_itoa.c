/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:58:22 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/25 14:08:56 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
	{
		len = 1;
		n *= -1;
	}
	while (n > 0)
	{
		n = n / 10;
		len ++;
	}
	return (len);
}

static char	*ft_reverse_dup(char *str, int n, int len)
{
	int	i;

	str[len] = '\0';
	i = len - 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		i--;
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = 0;
	str = "";
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str = ft_reverse_dup(str, n, len);
	return (str);
}
