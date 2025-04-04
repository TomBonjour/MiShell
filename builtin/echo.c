#include "../minishell.h"

// ECHO-util1 : Regarde si un argument de echo est une option -n	
int	ft_is_option(char *str)
{
	int	i;

	i = 2;
	if (str[0] == '-' && str[1] == 'n')
	{
		while (str[i] != '\0')
		{
			if (str[i] != 'n')
				return (0);
			else
				i++;
		}
		return (1);
	}
	return (0);
}

int	ft_skip_options(char **tab, int *i)
{
	int	opt;

	opt = ft_is_option(tab[1]);
	if (opt == 1)
	{
		*i = 2;
		while (tab[*i] != NULL && ft_is_option(tab[*i]) == 1)
			(*i)++;
	}
	if (opt == 1 && !tab[*i])
	{
		printf("");
		return (-1);
	}
	return (opt);
}

// COMMANDE ECHO
// 		Regarde si le 1er arg de echo, et les suivants sont des -n avec ECHO-util1
//		Print les arguments séparés par un espace, puis \n si il n'y a pas d'option
void	ft_echo(char **arg)
{
	int	i;
	int	opt;
	int	size;

	i = 1;
	size = 0;
	if (!arg[1])
	{
		printf("\n");
		return ;
	}
	while (arg[size] != NULL)
		size++;
	opt = ft_skip_options(arg, &i);
	if (opt == -1)
		return ;
	while (arg[i] != NULL)
	{
		printf("%s", arg[i]);
		if (i < size - 1 && arg[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (opt == 0)
		printf("\n");
}
