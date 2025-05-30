#include "../minishell.h"
#include "ft_dprintf.h"

// CD-3 : Remplace le contenu de la var. d'env. ~var avec le nouveau ~path
// 		Utilisée par CD-2 pour actualiser OLDPWD avant de changer de dir, 
// 		et actualiser PWD après le changement de dir
int	ft_set_env_var(char *var, char path[PATH_MAX], t_env *env)
{
	int	i;

	i = 0;
	while (env[i].name && ft_strncmp(env[i].name, var, ft_strlen(var)) != 0)
		i++;
	if (env[i].name == NULL)
	{
		ft_dprintf(2, "Warning : %s not set\n", var);
		return (0);
	}
	free(env[i].data);
	env[i].data = ft_strdup(path);
	if (!env[i].data)
		return (-1);
	return (0);
}

// CD-2 : Récupère le path actuel avec la #getcwd
// 		  Le remplace dans $OLDPWD avec CD-3 (ft_set_env_var)
// 		  Change de directory vers le ~newdir avec la #chdir
// 		  Récupère le nouveau path avec la #getcwd
// 		  Le remplace dans $PWD avec CD-3 (ft_set_env_var)
int	ft_change_dir_and_pwd(char *newdir, char path[PATH_MAX], t_env *env)
{
	if (getcwd(path, PATH_MAX) == NULL)
		return (-1);
	if (ft_set_env_var("OLDPWD", path, env) != 0)
		return (-1);
	if (chdir(newdir) != 0)
		return (-1);
	if (getcwd(path, PATH_MAX) == NULL)
		return (-1);
	if (ft_set_env_var("PWD", path, env) != 0)
		return (-1);
	return (0);
}

int	ft_cd_empty(char path[PATH_MAX], t_env *env, t_data *data)
{
	int		i;
	char	*newdir;

	i = 0;
	while (env[i].name && ft_strncmp(env[i].name, "HOME", 4) != 0)
		i++;
	if (env[i].name)
	{
		ft_pathcpy(path, env[i].data, ft_strlen(env[i].data));
		newdir = ft_strdup(path);
		if (!newdir)
			return (-1);
		if (ft_change_dir_and_pwd(newdir, path, env) == -1)
		{
			data->rvalue = 1;
			ft_dprintf(2, "Error using cd builtin\n");
		}
		free(newdir);
	}
	else
	{
		data->rvalue = 1;
		ft_dprintf(2, "HOME not set\n");
	}
	return (0);
}

void	ft_cd(char **tab, t_env *env, t_data *data)
{
	char	path[PATH_MAX];

	ft_memset(path, 0, PATH_MAX);
	if (!tab[1])
	{
		if (ft_cd_empty(path, env, data) == -1)
		{
			data->rvalue = 1;
			ft_dprintf(2, "Error using cd builtin\n");
		}
	}
	else
	{
		if (ft_change_dir_and_pwd(tab[1], path, env) == -1)
		{
			data->rvalue = 1;
			ft_dprintf(2, "No such file or directory\n");
		}
	}
}
