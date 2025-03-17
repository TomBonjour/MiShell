#include "../minishell.h"

char	*ft_fill_name(char *var, char c)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (var[i] != c)
		i++;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	while (j < i)
	{
		str[j] = var[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_fill_data(char *var, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (var[i] != c)
		i++;
	str = ft_strdup(var + i + 1);
	if (!str)
		return (NULL);
	return (str);
}
