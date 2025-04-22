#include "../../minishell.h"

void	ft_skip_quote(int *i, int *nb_quote, int *pos)
{
	*pos = *i - 1;
	(*i)++;
	*nb_quote += 1;
}

char	*ft_remove_quotes(char *str, char quote, int *pos, t_data *data)
{
	int		i;
	int		j;
	int		nb_quote;
	char	*new;

	ft_init_remove_quotes(&i, &j, &nb_quote);
	new = malloc(sizeof(char) * (ft_strlen(str) - 2 + 1));
	if (!new)
		return (ft_set_error(data, 1));
	while (i < *pos)
		new[j++] = str[i++];
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == quote && nb_quote < 2)
			ft_skip_quote(&i, &nb_quote, pos);
		if ((str[i] != quote || nb_quote >= 2) && str[i] != '\0')
			new[j++] = str[i++];
		else if (str[i] != '\0')
			i++;
	}
	new[j] = '\0';
	free(str);
	return (new);
}

int	ft_find_end_quote(char *s, int *i, char c)
{
	(*i)++;
	while (s[*i] != c && s[*i] != '\0')
		(*i)++;
	if (s[*i] == '\0')
	{
		ft_dprintf(2, "missing quote\n");
		return (-1);
	}
	return (0);
}

char	*ft_expand_quote(char *str, int *i, t_data *data)
{
	char	quote;
	int		pos;

	quote = str[*i];
	pos = *i;
	while (str[++*i] != quote && str[*i] != '\0')
	{
		if (str[*i] == '$' && quote == '"' && str[*i + 1]
			!= quote && ft_is_xpendable(str[*i + 1]) == 1)
		{
			if (str[*i + 1] == '?')
				str = ft_expand_quest_mark(str, *i, data);
			else if (ft_is_quote(str[*i + 1]) == 1)
				str = ft_remove_dollar(str, *i, data);
			else
				str = ft_expand_env_var(str, i, data);
			if (data->err == 1)
				return (NULL);
		}
	}
	str = ft_remove_quotes(str, quote, &pos, data);
	if (data->err == 1)
		return (NULL);
	(*i) = pos;
	return (str);
}

char	**ft_return_one_str(char *str, t_data *data)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (ft_set_error(data, 1));
	if (!str)
		tab[0] = "";
	else
		tab[0] = ft_strdup(str);
	tab[1] = NULL;
	return (tab);
}
