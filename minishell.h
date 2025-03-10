/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 08:09:33 by tobourge          #+#    #+#             */
/*   Updated: 2025/03/09 12:57:41 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <linux/limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_list
{
	char			**args;
	char			**redir;
	struct s_list	*next;
}					t_list;

typedef struct s_env
{
	char			*name;
	char			*data;
}					t_env;

//------ BUILTINS UTILS ------//
int		ft_pwd(void);
int		ft_env(char **envp);
void	ft_echo(char **tab);
int		ft_cd(char **tab, t_env *env);


//------ PARSING UTILS ------//
void	ft_parsing(char *input);
int		ft_get_command_and_redir(char *s, t_list **new_elem);
int		ft_arg_len(char *cmd, int i);
void	ft_redir_len(char *cmd, int *i);
void	ft_syntax_error(t_list **args, char *mess);
void	ft_find_end_quote(char *s, int *len, char c);
int		ft_count_redir(char *cmd);
int		ft_count_args(char *cmd);
char	*ft_redir_substr(char *cmd, int *i);
char	*ft_arg_substr(char *cmd, int *i);
char	*ft_realloc_char(char *str, char c);
t_list	*ft_tokenize(char *s);
int		ft_syntaxer(t_list *line);

//------ LISTS UTILS ------//
t_list	*ft_lst_new_node(char *s);
void	ft_lstadd_back(t_list **lst, t_list *lstnew);
void	ft_free_list(t_list **line);

//------ GENERAL UTILS ------//
void	ft_reverse_free(char **tab, int j);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_count_words(char *cmd);
int		ft_is_redir(char c);
int		ft_is_blank(char c);
int		ft_is_quote(char c);
char	*ft_strdup(char *s);
int		ft_strlen(char *str);
char	*ft_substr(char *s, int start, int len);
char	*ft_extract_quote(char *cmd, int *i, char *str, char quote);
char	*ft_extract_str(char *cmd, int *i, char *str);
void	ft_pathcpy(char s[4096], char *src, int size);
