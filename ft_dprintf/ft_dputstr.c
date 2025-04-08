#include "ft_dprintf.h"

void	ft_dputstr(int fd, char *string, size_t *written_char)
{
	if (!string)
	{
		write(fd, "(null)", 6);
		(*written_char) += 6;
		return ;
	}
	while (*string)
	{
		write(fd, string++, 1);
		(*written_char)++;
	}
}
