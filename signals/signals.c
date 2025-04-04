#include "../minishell.h"

void	ft_sigint_handler(int sig)
{
	(void)sig;
	g_errvalue = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sigquit_handler(int sig)
{
	(void)sig;
	readline("mangeducrabe> ");
}

void	setup_signals(void)
{
	signal(SIGINT, ft_sigint_handler);			// CTRL -C 
	signal(SIGQUIT, ft_sigquit_handler);		// CTRL-\ : quit and core dump
}
