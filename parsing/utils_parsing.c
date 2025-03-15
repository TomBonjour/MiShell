#include "../minishell.h"

// A FINIR !!! Free la list et exit le programme en affichant syntax_error
void	ft_syntax_error(t_list **args, char *mess)
{
	if (args == NULL)
		(void)args;
	if (mess == NULL)
		(void)mess;
	printf("Syntax error\n");
	ft_free_list(args);
	exit (0);
}

// Trouve la fin de la quote dans laquelle on est entré.
// Renvoie syntax error si la quote n'a pas de fin.
// 		Utilisée dès qu'on trouve une quote et qu'on veut la passer
void	ft_find_end_quote(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	if (s[*i] == '\0')
		ft_syntax_error(NULL, "missing quote");
}

// Renvoie la longueur du nom d'une variable d'env
int	ft_env_var_len(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i] == '_' || ft_isalpha(str[i]) == 1)
	{
		size++;
		i++;
	}
	return (size);
}

// Regarde dans une string si il y a une variable d'env ou des quotes
int	ft_need_to_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_is_quote(str[i]) == 1
			|| (str[i] == '$' && ft_is_xpendable(str[i + 1])))
			return (1);
		else
			i++;
	}
	return (0);
}

// Realloc une string en enlevant deux quotes
char	*ft_remove_quotes(char *str, char quote, int pos)
{
	int		i;
	int		j;
	char	*new;
	int		nb_quote;

	i = 0;
	j = 0;
	nb_quote = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) - 2 + 1));
	while (i < pos)
		new[j++] = str[i++];
	while (str[i] != '\0')
	{
		if (str[i] == quote && nb_quote < 2)
		{
			i++;
			nb_quote += 1;
		}
		if ((str[i] != quote || nb_quote >= 2) && str[i] != '\0')
			new[j++] = str[i++];
		else if (str[i] != '\0')
			i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

char 	*ft_remove_dollar(char *str, int i)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) - 1 + 1));
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	i++;
	while (str[i] != '\0')
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}
