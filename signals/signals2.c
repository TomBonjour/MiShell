#include "../minishell.h"

void	ft_sigint_handler_hdoc(int sig)
{
	(void)sig;
	g_errvalue = 128 + sig;
	rl_done = 1;
}

void	ft_sigint_handler_execve(int sig)
{
	(void)sig;
	g_errvalue = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	ft_sigquit_handler_execve(int sig)
{
	(void)sig;
	g_errvalue = 131;
	write(1, "Quit\n", 5);
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	modify_signals_hdoc(void)
{
	signal(SIGINT, ft_sigint_handler_hdoc);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	modify_signals_execve(void)
{
	signal(SIGINT, ft_sigint_handler_execve);
	signal(SIGQUIT, ft_sigquit_handler_execve);
	// signal(SIGPIPE, SIG_IGN);
	return (0);
}
