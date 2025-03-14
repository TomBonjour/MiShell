#include "../minishell.h"

void	ft_reverse_free(char **tab, int j)
{
	while (j > 0)
	{
		free(tab[j - 1]);
		j--;
	}
	free(tab);
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
char	*ft_realloc_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (NULL);
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
char	*ft_extract_quote(char *cmd, int *i, char *str, char quote)
{
	if (quote == '\0')
		quote = cmd[*i];
	str = ft_realloc_char(str, cmd[*i]);
	if (!str)
		return (NULL);
	(*i)++;
	while (cmd[*i] != quote)
	{
		str = ft_realloc_char(str, cmd[*i]);
		if (!str)
			return (NULL);
		(*i)++;
	}
	str = ft_realloc_char(str, cmd[*i]);
	if (!str)
		return (NULL);
	(*i)++;
	return (str);
}

// Extrait un argument entier
char	*ft_extract_str(char *cmd, int *i, char *str)
{
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0
		&& cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, cmd[*i]);
		else
		{
			str = ft_realloc_char(str, cmd[*i]);
			if (!str)
				return (NULL);
			(*i)++;
		}
	}
	return (str);
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
