/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:50:54 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/01 22:00:48 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" 

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

int	main(void)
{
	char	*input = ">           y<yy>j<f";
	// char	*input = "<< here cat";
	t_list	*line;
	int		i;
	int		j;

	i = 0;
	j = 1;
	/*setup_signals();
	while (1)
	{
		input = readline("mangeducrabe> ");
		if (!input)
		{
			write(2, "Exit\n", 5);
			break;
		}
		add_history(input);*/
		line = ft_tokenize(input);
		//ft_parsing(input);
		while (line != NULL)
		{
			i = 0;
			printf ("COMMANDE %d\n", j);
			while (line->args[i] != NULL)
			{
				printf("|%s|", line->args[i]);
				i++;
			}
			printf("\n");
			i = 0;
			printf("\nREDIRECTIONS %d\n", j);
			while (line->redir[i] != NULL)
			{
				printf("|%s|", line->redir[i]);
				i++;
			}
			printf("\n");
			printf("--------------\n |\n v\n--------------\n");
			line = line->next;
			j++;
		}
		printf("NULL");
		//ft_free_list(&line);
	//}
	return (0);
}


