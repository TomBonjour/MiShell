#include "../minishell.h"

int	ft_check_syntax(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!ft_isdigit((int)str[i]))
		return (1);
	while (str[i] != '\0')
	{
		if (!ft_isdigit((int)str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_for_long_minmax(char *str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		count = 0;
		if (str[i] == '-' || str[i] == '+')
			i++;
		while (str[i] == '0')
			i++;
		while (str[i] >= '0' && str[i] <= '9')
		{
			count++;
			i++;
		}
		if (count > 19)
			return (1);
	}
	return (0);
}

int	ft_increment(long long *n, int sign, char *str, int i)
{
	if ((*n) * sign > LLONG_MAX / 10 || (*n) * sign < LLONG_MIN / 10)
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", str);
		return (2);
	}
	(*n) *= 10;
	if ((*n) * sign > LLONG_MAX - (str[i] - 48)
		|| (*n) * sign < LLONG_MIN + (str[i] - 48))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", str);
		return (2);
	}
	(*n) += str[i] - 48;
	return (0);
}

int	ft_parsing_exit(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	if (i == 1)
		return (3);
	if (ft_check_syntax(argv[1]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", argv[1]);
		return (2);
	}
	else if (ft_check_for_long_minmax(argv[1]))
	{
		ft_dprintf(2, "exit: %s: numeric argument required\n", argv[1]);
		return (2);
	}
	else if (i > 2)
	{
		ft_dprintf(2, "exit: too many arguments\n"); /*ne quitte pas le prgm*/
		return (1);
	}
	return (0);
}

int	ft_exit(t_list *line, t_env *env, t_data *data)
{
	if (data->nodes == 1)
		ft_dprintf(2, "exit\n");
	data->rvalue = ft_parsing_exit(line->args);
	if (data->rvalue != 1)
	{
		if (data->rvalue == 3)
			data->rvalue = 0;
		else if (data->rvalue < 1 || data->rvalue > 3)
			data->rvalue = ft_atoll(line->args[1]);
		ft_free_tab(data->paths, 0);
		ft_free_env(env);
		ft_free_list(&line);
		exit (data->rvalue);
	}
	return (data->rvalue);
}
