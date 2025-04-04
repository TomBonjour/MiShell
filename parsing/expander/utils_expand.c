#include "../../minishell.h"

// Renvoie la longueur du nom d'une variable d'env
int	ft_env_var_len(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i] == '_' || ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1)
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

char	*ft_remove_dollar(char *str, int i, t_data *data)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc (sizeof(char) * (ft_strlen(str) - 1 + 1));
	if (!new)
		return (ft_set_error(data, 1));
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
