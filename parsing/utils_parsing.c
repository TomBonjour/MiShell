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

int	ft_env_var_len(char *str, int i)
{
	int size;

	size = 0;
	while (str[i] == '_' || ft_isalpha(str[i]) == 1)
	{
		size++;
		i++;
	}
	return (size);
}

/*void	ft_remove_quote(t_list *line)
{
	
}*/
