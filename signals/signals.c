#include "../minishell.h"

int	event(void)
{
	return (0);
}

void	ft_sigint_handler(int sig)
{
	(void)sig;
	g_errvalue = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	g_errvalue = 0;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
