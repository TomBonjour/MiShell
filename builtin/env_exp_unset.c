#include "../minishell.h"


// COMMANDE ENV : imprime la copie du tableau de variables d'environnement
int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i].name != NULL)
	{
		printf("%s=%s\n", env[i].name, env[i].data);
		i++;
	}
	return (0);
}

/*int	ft_export(char **tab, t_env *env)
{

}


int	ft_unset(char **tab, t_env *env)
{

}*/
