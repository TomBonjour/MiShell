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

int	ft_is_var_only(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '$')
	{
		printf("var denv pas seule\n");
		return (0);
	}
	while (str[i] == '_' || ft_isalpha(str[i]) == 1 || ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] == '\0')
	{
		printf("var denv seule\n");
		return (1);
	}
	printf("var denv pas seule\n");
	return (0);
}
