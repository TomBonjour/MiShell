#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <limits.h>

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

typedef struct s_data
{
	int				rvalue;
}					t_data;

//------ BUILTINS UTILS ------//
int			ft_pwd(void);
int			ft_env(t_env *env);
void		ft_echo(char **tab);
int			ft_cd(char **tab, t_env *env);
int			ft_forbidd_char(char *var);
int			ft_find_equal(char *var);
int			ft_find_var(t_env *env, char *var, int *i);
int			ft_export_fill_env(t_env *new_tab, char *var, t_env *env);
t_env		*ft_export(char **argv, t_env *env);
char		*ft_fill_name(char *var, char c);
char		*ft_fill_data(char *var, char c);
t_env		*ft_unset(char **argv, t_env *env);
void		ft_unset_fill_env(t_env *new_tab, char *var, t_env *env, int i);
int			ft_unset_find_var(char *var, t_env *env);
t_env		*ft_realloc_env(int i);
int			ft_exit(char **argv, t_list *line, t_env *env, t_data *data);
int			ft_parsing_exit(char **argv);
long long	ft_atoll(char *str);
int			ft_check_syntax(char *str);
int			ft_increment(long long *n, int sign, char *str, int i);

//------ SIGNALS UTILS ------//
void		ft_sigint_handler(int sig);
void		ft_sigquit_handler(int sig);
void		setup_signals(void);

//------	 PARSING UTILS ------//
void		ft_parsing(char *input);
int			ft_get_command_and_redir(char *s, t_list **new_elem);
int			ft_arg_len(char *cmd, int i);
void		ft_redir_len(char *cmd, int *i);
void		ft_syntax_error(t_list **args, char *mess);
void		ft_find_end_quote(char *s, int *len, char c);
int			ft_count_redir(char *cmd);
int			ft_count_args(char *cmd);
char		*ft_redir_substr(char *cmd, int *i);
char		*ft_arg_substr(char *cmd, int *i);
char		*ft_realloc_char(char *str, char c);
t_list		*ft_tokenize(char *s);
int			ft_syntax_and_expand(t_list *line, t_env *env, t_data *data);
char		*ft_expander(char *str, t_env *env, t_data *data);
int			ft_env_var_len(char *str, int i);
int			ft_need_to_expand(char *str);
char		*ft_remove_quotes(char *str, char quote, int pos, int nb_quotes);
char		*ft_remove_dollar(char *str, int i);
char		**ft_heredoc_priority(char **redir_tab, int size);

//------	 LISTS UTILS ------//
t_list		*ft_lst_new_node(char *s);
void		ft_free_list(t_list **line);
void		ft_free_env(t_env *env);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_init_data(t_data *data);

//------	 GENERAL UTILS ------//
void		ft_reverse_free(char **tab, int j);
int			ft_count_words(char *cmd);
int			ft_is_redir(char c);
int			ft_is_blank(char c);
int			ft_is_quote(char c);
int			ft_is_env_var(char c);
int			ft_is_xpendable(char c);
char		*ft_extract_quote(char *cmd, int *i, char *str, char quote);
char		*ft_extract_str(char *cmd, int *i, char *str);
char		*ft_pathcpy(char s[PATH_MAX], char *src, int size);

#endif
