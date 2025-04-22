/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dusint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:31 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:20:32 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dusint(int fd, int n, size_t *written_char)
{
	unsigned int	nb;

	if (n < 0)
		return ;
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
