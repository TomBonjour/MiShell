#include <minishell.h>

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
