#include "../minishell.h"

char	*ft_strjoin_equal(char *s1, char *s2, t_data *data)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	i = -1;
	j = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 2));
	if (!str)
		return (ft_set_error(data, 1));
	while (s1[++i] != '\0')
		str[i] = s1[i];
	str[i] = '=';
	i++;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_convert_env(t_env *env, t_data *data)
{
	char	**envtab;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (env[i].name != NULL)
		i++;
	envtab = malloc(sizeof(char *) * (i + 1));
	if (!envtab)
		return (ft_set_error(data, 1));
	i = 0;
	while (env[i].name != NULL)
	{
		envtab[i] = ft_strjoin_equal(env[i].name, env[i].data, data);
		if (data->err == 1)
			return (NULL);
		i++;
	}
	envtab[i] = NULL;
	return (envtab);
}
