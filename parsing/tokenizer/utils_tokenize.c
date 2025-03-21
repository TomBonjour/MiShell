#include "../../minishell.h"

// Compte le nombre d'arguments non-redir dans la string
// --> Utilisée pour malloc le tableau de commande/arguments
int	ft_count_args(char *cmd, int i)
{
	int	n;

	n = 0;
	while (cmd[i] != '\0')
	{
		while (ft_is_redir(cmd[i]) == 1)
		{
			if (ft_redir_len(cmd, &i) == -1)
				return (-1);
		}
		if (cmd[i] != '\0')
			n++;
		while (ft_is_blank(cmd[i]) == 0 && ft_is_redir(cmd[i]) == 0 && cmd[i])
		{
			if (ft_is_quote(cmd[i]) == 1)
			{
				if (ft_find_end_quote(cmd, &i, cmd[i]) == -1)
					return (-1);
			}
			i++;
		}
		while (ft_is_blank(cmd[i]) == 1 && cmd[i] != '\0')
			i++;
	}
	return (n);
}

// Extrait l'argument dans une string malloquée en format "xxxx"
// --> Utilisée pour remplir le tableau de commande/arguments
char	*ft_arg_substr(char *cmd, int *i, t_data *data)
{
	char	*str;

	str = malloc(sizeof(char) * 1);
	if (!str)
		return (ft_set_error(data, 1));
	str[0] = '\0';
	while (ft_is_blank(cmd[*i]) == 0 && ft_is_redir(cmd[*i]) == 0 && cmd[*i])
	{
		if (ft_is_quote(cmd[*i]) == 1)
			str = ft_extract_quote(cmd, i, str, data);
		else
			str = ft_extract_str(cmd, i, str, data);
		if (data->err == 1)
			return (NULL);
	}
	while (ft_is_blank(cmd[*i]) == 1 && cmd[*i] != '\0')
		(*i)++;
	return (str);
}
