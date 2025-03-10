/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 11:57:51 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 11:58:34 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*void	ft_sigint_handler(int sig)
{
	(void)sig;
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
	signal(SIGINT, ft_sigint_handler);			// CTRL-C : kill the process
	signal(SIGQUIT, ft_sigquit_handler);		// CTRL-\ : quit and core dump
}*/
