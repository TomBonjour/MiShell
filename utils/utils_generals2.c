#include <minishell.h>

int	ft_is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

int	ft_is_env_var(char c)
{
	if (c == '_' || ft_isalpha(c) == 1)
		return (1);
	else
		return (0);
}

int	ft_is_xpendable(char c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1
		|| c == '_' || c == '?' || c == '"' || c == '\'')
		return (1);
	else
		return (0);
}

int	ft_is_heredoc_xpendable(char c)
{
	if (ft_isalpha(c) == 1 || c == '_' || c == '?')
		return (1);
	else
		return (0);
}

void	ft_close_fds(t_data *data, int flag)
{
	int	i;

	i = 3;
	while (i < 1023)
	{
		if (i != data->fdtmp)
			close (i);
		i++;
	}
	if (flag == 0)
		close(data->fdtmp);
}
