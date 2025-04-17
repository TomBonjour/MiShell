#include "../minishell.h"

int	event(void)
{
	return (0);
}

void	ft_sigint_handler(int sig)
{
	// __builtin_debugtrap();
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
	signal(SIGINT, ft_sigint_handler);			// CTRL -C 
	signal(SIGQUIT, SIG_IGN);		// CTRL-\ : quit and core dump
}

void	reset_signals()
{
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	// signal(SIGPIPE, SIG_DFL);
}
