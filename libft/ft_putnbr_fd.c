/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:12:45 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/25 14:22:55 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + 48, fd);
	if (n < 0 && n >= -9)
	{
		write(fd, "-", 1);
		ft_putchar_fd(-n + 48, fd);
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n < -9 && n != -2147483648)
	{
		write(fd, "-", 1);
		ft_putnbr_fd((n * (-1)) / 10, fd);
		ft_putnbr_fd((n * (-1)) % 10, fd);
	}
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
}
