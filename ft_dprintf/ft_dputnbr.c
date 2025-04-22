/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:50 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:20:51 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dputnbr(int fd, int n, size_t *written_char)
{
	int	nb;

	if (n == INT_MIN)
	{
		write(fd, "-2147483648", 11);
		*written_char += 11;
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		(*written_char)++;
	}
	if (n > 9)
	{
		ft_dputnbr(fd, n / 10, written_char);
		ft_dputnbr(fd, n % 10, written_char);
	}
	else
	{
		nb = n + 48;
		write(fd, &nb, 1);
		(*written_char)++;
	}
}
