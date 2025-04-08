#include "ft_dprintf.h"

void	ft_dputchar(int fd, char c, size_t *written_char)
{
	write(fd, &c, 1);
	(*written_char)++;
}
