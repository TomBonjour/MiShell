#include "../minishell.h"

long long	ft_atoll(char *str)
{
	int			i;
	long long	n;
	int			sign;

	i = 0;
	n = 0;
	sign = 1;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ft_increment(&n, sign, str, i))
			return (2);
		i++;
	}
	return (n * sign);
}

void	ft_error_manager(t_data *data, t_list **line, t_env *env)
{
	if (data->err == 1)
		ft_free_and_exit(*line, env);
	if (data->err == 2)
		ft_syntax_error(line, data);
}

void	*ft_set_error(t_data *data, int n)
{
	data->err = n;
	data->rvalue = 2;
	return (NULL);
}

void	ft_reverse_free(char **tab, int j)
{
	while (j > 0)
	{
		free(tab[j - 1]);
		j--;
	}
	free(tab);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
