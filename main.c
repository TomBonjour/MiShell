#include "minishell.h" 

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_env 		*env;
	t_data		data;
	char		*input;  
	t_list		*line;
	int			exit_status;
	// t_list		*temp;
	int			i;
	int			j;
	// int		value_exit;

	i = 0;
	j = 1;

	// Copie de la liste de variables d'env (char **envp)
	// dans un tableau de structure (t_env *env)
	ft_init_data(&data);
	env = ft_set_env(envp, &data);
	if (data.err != 0)
	{
		ft_error_manager(&data, &line, env);
		return (0);
	}
	data.env = env;

	// Mise en place des signaux (SIGINT, SIGQUIT)
	setup_signals();

	while (1)
	{
		input = readline("mangeducrabe> ");
		if (!input)
		{
			//write(2, "Exit\n", 5);
			break;
		}
		add_history(input);
		line = ft_tokenize(input, &data);
		if (data.err != 0)
			ft_error_manager(&data, &line, env);
		free(input);
		ft_syntax_and_expand(line, env, &data);
		if (data.err != 0)
			ft_error_manager(&data, &line, env);
		ft_exec_cmd(line, env, &data);
		if (data.err != 0)
			ft_error_manager(&data, &line, env);
		exit_status = ft_wait_pid(&data);
		ft_free_list(&line);
		//PRINT LISTE CHAINEE
		/*temp = line;
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
		printf("NULL\n");
		line = temp;*/
	}
	//TEST COMMANDES 
	//ft_env(env);
	//ft_pwd();
	// ft_echo(line->args);
	// ft_cd(line->args, env);
	// env = ft_unset(line->args[1], env);
	/*while (env[i].name != NULL)
	{
		printf("%s=%s\n", env[i].name, env[i].data);
		i++;
	}*/
	// value_exit = ft_exit(line->args, line, env, &data);
	
	ft_close_fds(&data, 0);
	ft_free_env(env);
	return (0);
	//return (value_exit);
}
