#include "../minishell.h"

char	*ft_fill_name(char *var, int flag)
{
	int		size;
	char	*str;
	int		i;

	i = 0;
	size = ft_strlen(var);
	while (var[i] != '=')
		i++;
	if (flag == 1)
	{
		if (var[i - 1] == '+')
			i--;
		str = ft_substr(var, 0, i);
	}
	else
		str = ft_substr(var, i + 1, size - i);
	if (!str)
		return (NULL);
	return (str);
}
