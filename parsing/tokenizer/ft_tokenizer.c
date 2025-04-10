#include "../../minishell.h"

void	*ft_malloc_arrays(char *cmd, t_list **new, t_data *data)
{
	int	i;

	i = 0;
	(*new)->nb_args = ft_count_args(cmd, i);
	if ((*new)->nb_args == -1)
		return (ft_set_error(data, 2));
	(*new)->nb_redir = ft_count_redir(cmd);
	if ((*new)->nb_redir == -1)
		return (ft_set_error(data, 2));
	(*new)->args = malloc(sizeof(char *) * ((*new)->nb_args + 1));
	(*new)->redir = malloc(sizeof(char *) * ((*new)->nb_redir + 1));
	(*new)->quote = malloc(sizeof(int) * ((*new)->nb_redir));
	if (!(*new)->args || !(*new)->redir || !(*new)->quote)
		return (ft_set_error(data, 1));
	return (0);
}

// Compte le nombre d'arguments et de redirections dans la commande, malloc
// Parcoure la string et envoie la position a ft_arg_substr() si il trouve
// un argument et a ft_redir_substr() si il trouve une redirection
// 	Remplit les tableaux avec les sub-string renvoyées par ces fonctions
void	*ft_get_cmd_and_redir(char *cmd, int i, t_list **new, t_data *data)
{
	int	j;
	int	k;

	j = -1;
	k = -1;
	if (ft_malloc_arrays(cmd, new, data) == NULL && data->err != 0)
		return (NULL);
	while (cmd[i] != '\0')
	{
		if (ft_is_redir(cmd[i]) == 1)
		{
			(*new)->redir[++j] = ft_redir_substr(cmd, &i, new, data);
			if ((*new)->quote_hdoc == 1)
				(*new)->quote[j] = 1;
			else
				(*new)->quote[j] = 0;
			(*new)->quote_hdoc = 0;
		}
		else
			(*new)->args[++k] = ft_arg_substr(cmd, &i, data);
		if (data->err == 1)
			return (NULL);
	}
	if ((*new)->nb_redir > 0)
	{
		(*new)->last_infile = ft_last_infile(*new, (*new)->nb_redir);
		(*new)->redir = ft_hdoc_prio((*new)->redir, (*new)->nb_redir, new, data);
	}
	if (data->err != 0)
		return (NULL);
	(*new)->redir[++j] = NULL;
	(*new)->args[++k] = NULL;
	return (0);
}

// 3. Tronque les espaces restant de la commande
// 		Envoie la string a lst_new() pour créer le nouveau node
// 		Envoie le nouveau node a lst_add_back() l'ajouter a la liste existante
t_list	**ft_new_add_back(char *s, int len, t_list **args, t_data *data)
{
	t_list	*new_arg;
	char	*cmd;

	if (len > 0)
	{
		while (ft_is_blank(s[len - 1]) == 1 && len > 0)
			len--;
	}
	cmd = ft_substr(s, 0, len);
	if (!cmd)
		return (ft_set_error(data, 1));
	new_arg = ft_lst_new_node(cmd, data);
	if (data->err == 1)
	{
		free(cmd);
		return (NULL);
	}
	free(cmd);
	ft_lstadd_back(args, new_arg);
	return (args);
}

// 2. Enleve les blank et split par les pipes
// 		Envoie chaque partie a lst_new_add_back(3) pour créer la liste chainee
t_list	*ft_split_line(char *s, t_list *args, int len, t_data *data)
{
	while (*s != '\0')
	{
		while (ft_is_blank(*s) == 1)
			s++;
		len = 0;
		while (s[len] != '|' && s[len] != '\0')
		{
			if (ft_is_quote(s[len]) == 1)
				if (ft_find_end_quote(s, &len, s[len]) == -1)
					return (ft_set_error(data, 2));
			len++;
		}
		if (s[len] == '\0')
		{
			if (ft_new_add_back(s, len, &args, data) == NULL && data->err == 1)
				return (NULL);
			return (args);
		}
		if (s[len] == '|')
		{
			if (ft_new_add_back(s, len, &args, data) == NULL && data->err == 1)
				return (NULL);
			s += len;
		}
		s++;
	}
	return (args);
}

// 1. Split (|) l'input en commandes avec split_line(2)

t_list	*ft_tokenize(char *s, t_data *data)
{
	t_list	*line;
	int		len;

	if (s == NULL)
		return (NULL);
	len = 0;
	line = NULL;
	while (ft_is_blank(*s) == 1)
		s++;
	if (*s == '\0')
		return (NULL);
	line = ft_split_line(s, line, len, data);
	if (!line)
		return (NULL);
	data->nodes = ft_count_nodes(line);
	return (line);
}
