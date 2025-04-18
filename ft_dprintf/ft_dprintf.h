#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <limits.h>

int		ft_dprintf(int fd, const char *format, ...);
void	ft_dhexa(int fd, unsigned int value,
			size_t *writ_char, const char form);
void	ft_dputchar(int fd, char c, size_t *written_char);
void	ft_dputnbr(int fd, int n, size_t *written_char);
void	ft_dputptr(int fd, void *ptr, size_t *written_char);
void	ft_dputstr(int fd, char *string, size_t *written_char);
void	ft_dusint(int fd, int n, size_t *written_char);

#endif
