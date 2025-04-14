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
	signal(SIGINT, ft_sigint_handler);			// CTRL -C 
	signal(SIGQUIT, SIG_IGN);		// CTRL-\ : quit and core dump
}

void	ft_sigquit_handler_hdoc(int	sig)
{
	(void)sig;
	readline("> ");
}
void	ft_sigint_handler_hdoc(int sig)
{
	(void)sig;
	g_errvalue = 128 + sig;
	rl_done = 1;
}
void	ft_sigint_handler_execve(int sig)
{
	(void)sig;
	g_errvalue = 128 + sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

int	modify_signals_hdoc()
{
	signal(SIGINT, ft_sigint_handler_hdoc);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	modify_signals_execve()
{
	signal(SIGINT, ft_sigint_handler_execve);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
