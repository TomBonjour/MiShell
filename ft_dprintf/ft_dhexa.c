#include "ft_dprintf.h"

void	ft_dhexa(int fd, unsigned int value, size_t *writ_char, const char form)
{
	const char		*base;
	unsigned int	num;

	base = "0123456789abcdef";
	if (value > 15)
	{
		ft_dhexa(fd, value / 16, writ_char, form);
		ft_dhexa(fd, value % 16, writ_char, form);
	}
	else
	{
		num = base[value];
		if (form == 'X')
		{
			if (num >= 'a' && num <= 'f')
				num -= 32;
		}
		write(1, &num, 1);
		(*writ_char)++;
	}
}
