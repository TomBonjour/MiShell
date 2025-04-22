#include "minishell.h" 

int	g_errvalue = 0;

void	ft_minishell(t_env *env, t_data *data, char *input, t_list *line)
{
	while (1)
	{
		setup_signals();
		input = readline("minishell> ");
		if (!input)
			break ;
		if (input[0] != '\0')
			add_history(input);
		line = ft_tokenize(input, data);
		if (data->err != 0)
			ft_error_manager(data, &line, env);
		free(input);
		ft_syntax_and_expand(line, data);
		if (data->err != 0)
			ft_error_manager(data, &line, env);
		ft_exec_cmd(line, data);
		if (data->err != 0)
			ft_error_manager(data, &line, env);
		ft_free_list(&line);
		dup2(STDOUT_FILENO, 1);
		dup2(STDIN_FILENO, 0);
		data->err = 0;
		data->rvalue = ft_wait_pid(data);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_data	data;
	char	*input;
	t_list	*line;

	(void)ac;
	(void)av;
	line = NULL;
	input = NULL;
	ft_init_data(&data);
	env = ft_set_env(envp, &data);
	if (data.err != 0)
	{
		ft_error_manager(&data, &line, env);
		return (0);
	}
	data.env = env;
	ft_minishell(env, &data, input, line);
	clear_history();
	ft_close_fds(&data, 0);
	ft_free_env(data.env);
	return (data.rvalue);
}
