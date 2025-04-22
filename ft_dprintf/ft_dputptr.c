/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:20:43 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:20:43 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	ft_writeptr(int fd, size_t address, size_t *written_char)
{
	const char	*base;
	size_t		num;

	base = "0123456789abcdef";
	if (address > 15)
	{
		ft_writeptr(fd, address / 16, written_char);
		ft_writeptr(fd, address % 16, written_char);
	}
	else
	{
		num = base[address];
		write(fd, &num, 1);
		(*written_char)++;
	}
}

void	ft_dputptr(int fd, void *ptr, size_t *written_char)
{
	size_t	address;

	if (!ptr)
	{
		write(fd, "(nil)", 5);
		(*written_char) += 5;
		return ;
	}
	write(fd, "0x", 2);
	*(written_char) += 2;
	address = (size_t) ptr;
	ft_writeptr(fd, address, written_char);
}
