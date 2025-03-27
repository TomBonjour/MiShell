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

void	ft_free_and_exit(t_list *line, t_env *env)
{
	ft_free_env(env);
	ft_free_list(&line);
	exit (2);
}

char	*ft_pathcpy(char str[PATH_MAX], char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < size)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

// Re-malloc +1 une chaine de caractere et rajoute le char ~c
char	*ft_realloc_char(char *str, char c, t_data *data)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (ft_set_error(data, 1));
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	i++;
	new[i] = '\0';
	free(str);
	return (new);
}

// Extrait une chaine de caractère entre quotes
char	*ft_extract_quote(char *cmd, int *i, char *str, t_data *data)
{
	int	quote;
	
	quote = cmd[*i];
	str = ft_realloc_char(str, cmd[*i], data);
	if (data->err == 1)
		return (NULL);
	(*i)++;
	while (cmd[*i] != quote)
	{
		str = ft_realloc_char(str, cmd[*i], data);
		if (data->err == 1)
			return (NULL);
		(*i)++;
	}
	str = ft_realloc_char(str, cmd[*i], data);
	if (data->err == 1)
		return (NULL);
	(*i)++;
	return (str);
}

// Extrait un argument entier
char	*ft_extract_str(char *cmd, int *i, char *str, t_data *data)
{
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0
		&& cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, data);
		else
		{
			str = ft_realloc_char(str, cmd[*i], data);
			(*i)++;
		}
		if (data->err == 1)
			return (NULL);
	}
	return (str);
}

int	ft_find_word(char *s, char *word)
{
	int	i;

	i = 0;
	if (ft_strlen(word) == ft_strlen(s))
	{
		while (word[i] == s[i] && word[i] != '\0' && s[i] != '\0')
			i++;
		if (word[i] == '\0' && s[i] == '\0')
			return (1);
	}
	return (-1);
}

int	ft_is_blank(char c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_is_redir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	else
		return (0);
}

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
	if (ft_isalpha(c) == 1 || c == '_' || c == '?' || c == '"' || c == '\'')
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

