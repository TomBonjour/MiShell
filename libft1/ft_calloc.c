/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:10:35 by tobourge          #+#    #+#             */
/*   Updated: 2024/10/29 15:00:00 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	size_malloc;
	size_t	max;

	max = -1;
	if (size != 0 && nmemb > max / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	size_malloc = size * nmemb;
	ptr = malloc(size_malloc);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size_malloc);
	return (ptr);
}
