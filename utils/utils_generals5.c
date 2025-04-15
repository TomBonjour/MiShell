#include <../minishell.h>

char	**ft_join_content_before(char **split, char *str, t_data *data)
{
	char	*join;
	char	*before;
	int		size;
	int		i;

	size = 0;
	i = -1;
	while (str[size] != '$')
		size++;
	before = malloc(sizeof(char) * (size + 1));
	if (!before)
		return (ft_set_error(data, 1));
	while (str[++i] != '$')
		before[i] = str[i];
	before[i] = '\0';
	join = ft_strjoin(before, split[0]);
	if (!join)
		return (ft_set_error(data, 1));
	free(before);
	free(split[0]);
	split[0] = ft_strdup(join);
	if (!split[0])
		return (ft_set_error(data, 1));
	free(join);
	return (split);
}
