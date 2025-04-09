#include <minishell.h>

void	ft_free_and_exit(t_list *line, t_env *env)
{
	ft_free_env(env);
	ft_free_list(&line);
	exit (2);
}

char	*ft_pathcpy(char str[PATH_MAX], char *src, int size)
{
	int	i;

	i = 0;
	while (src[i] != '\0' && i < size)
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

// Re-malloc +1 une chaine de caractere et rajoute le char ~c
char	*ft_realloc_char(char *str, char c, t_data *data)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!new)
		return (ft_set_error(data, 1));
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = c;
	i++;
	new[i] = '\0';
	free(str);
	return (new);
}

void	ft_free_env(t_env *env)
{
	int	j;

	j = 0;
	while (env[j].name != NULL)
	{
		free(env[j].name);
		free(env[j].data);
		j++;
	}
	free(env);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	return (i);
}
