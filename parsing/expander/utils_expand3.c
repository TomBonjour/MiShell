#include "../../minishell.h"

char	**ft_split_join(char **split, char **tab, int n, t_data *data)
{
	if (tab[n][0] != '$')
	{
		split = ft_join_content_before(split, tab[n], data);
		if (data->err == 1)
			return (ft_set_error(data, 1));
	}
	return (split);
}

void	ft_init_remove_quotes(int *i, int *j, int *nb_quote)
{
	*i = 0;
	*j = 0;
	*nb_quote = 1;
}
