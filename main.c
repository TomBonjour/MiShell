#include "minishell.h" 

// Copie du contenu de la variable dans la partie "data" de la structure t_env
int	ft_copy_env_data(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '\0')
		(*i)++;
	(*i) -= ft_strlen(env[j].name) + 1;
	env[j].data = malloc(sizeof(char) * (*i + 1));
	if (!env[j].data)
		return (-1);
	env[j].data[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].data[*i] = envp[j][*i + ft_strlen(env[j].name) + 1];
		(*i)--;
	}
	return (0);
}

// Copie du nom de la variable dans la partie "name" de la structure
int	ft_copy_env_name(char **envp, t_env *env, int j, int *i)
{
	while (envp[j][*i] != '=')
		(*i)++;
	env[j].name = malloc(sizeof(char) * (*i + 1));
	if (!env[j].name)
		return (-1);
	env[j].name[*i] = '\0';
	(*i)--;
	while (*i >= 0)
	{
		env[j].name[*i] = envp[j][*i];
		(*i)--;
	}
	return (0);
}

// Création du nouveau tableau de variables d'environnement
// --> un tableau de structures {char *name ; char *data}
t_env	*ft_set_env(char **envp, t_data *data)
{
	int		i;
	int		j;
	t_env	*env;

	j = 0;
	while (envp[j] != NULL)
		j++;
	env = malloc(sizeof(t_env) * (j + 1));
	if (!env)
		return (ft_set_error(data, 1));
	j = 0;
	while (envp[j] != NULL)
	{
		i = 0;
		if (ft_copy_env_name(envp, env, j, &i) == -1)
			return (ft_set_error(data, 1));
		i = ft_strlen(env[j].name) + 2;
		if (ft_copy_env_data(envp, env, j, &i) == -1)
			return (ft_set_error(data, 1));
		j++;
	}
	env[j].name = NULL;
	env[j].data = NULL;
	return (env);
}

void	ft_free_env(t_env *env)
{
	int	j;

	j = 0;
	while (env[j].name != NULL)
	{
		free(env[j].name);
		free(env[j].data);
		j++;
	}
	free(env);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	(void)envp;
	t_env 	*env;
	t_data	data;
	char	*input = "echo arg1 \"arg 2\" arg3";  
	t_list	*line;
	t_list	*temp;
	int		i;
	int		j;
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


	// Mise en place des signaux (SIGINT, SIGQUIT)
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
		line = ft_tokenize(input, &data);
		if (data.err != 0)
		{
			ft_error_manager(&data, &line, env);
			return (0);
		}
		ft_syntax_and_expand(line, env, &data);
		if (data.err != 0)
		{
			ft_error_manager(&data, &line, env);
			return (0);
		}
			
		//PRINT LISTE CHAINEE
		temp = line;
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
		line = temp;
//	}
	

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
	ft_free_env(env);
	ft_free_list(&line);
	return (0);
	//return (value_exit);
}
