#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <signal.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <limits.h>
# include <sys/wait.h>

typedef struct s_list
{
	char			**args;
	char			**redir;
	int				hdoc;
	int				fd_hdoc;
	int				inf;
	int				fd_infile;
	int				last_infile;
	int				outf;
	int				fd_outfile;
	int				builtin;
	char			*pathname;
	struct s_list	*next;
}					t_list;

typedef struct s_env
{
	char			*name;
	char			*data;
}					t_env;

typedef struct s_data
{
	t_env	*env;
	int		err;
	int		rvalue;
	int		pid;
	int		fdtmp;
	int		nodes;
	int		node_pos;
	char	**paths;
}		t_data;

typedef struct s_heredoc
{
	char	*eof;
	char	*str;
	char	*filename;
	int		size;
}			t_hdoc;

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
int			ft_exit(t_list *line, t_env *env, t_data *data);
int			ft_parsing_exit(char **argv);
long long	ft_atoll(char *str);
int			ft_check_syntax(char *str);
int			ft_increment(long long *n, int sign, char *str, int i);
int			ft_alloc_newenv(t_env **env, int i);

//------ SIGNALS UTILS ------//
void		ft_sigint_handler(int sig);
void		ft_sigquit_handler(int sig);
void		setup_signals(void);
void		ft_init_var(t_hdoc *infos, int flag);
int			ft_heredoc(t_list *line, t_hdoc *infos, t_data *data);

//------	 PARSING UTILS ------//
void		ft_parsing(char *input);
void		*ft_get_cmd_and_redir(char *s, int i, t_list **new_e, t_data *data);
int			ft_arg_len(char *cmd, int i);
int			ft_redir_len(char *cmd, int *i);
void		ft_syntax_error(t_list **args, t_data *data);
int			ft_find_end_quote(char *s, int *len, char c);
int			ft_count_redir(char *cmd);
int			ft_count_args(char *cmd, int i);
char		*ft_redir_substr(char *cmd, int *i, t_data *data);
char		*ft_arg_substr(char *cmd, int *i, t_data *data);
char		*ft_realloc_char(char *str, char c, t_data *data);
t_list		*ft_tokenize(char *s, t_data *data);
void		*ft_syntax_and_expand(t_list *line, t_env *env, t_data *data);
char		*ft_expander(char *str, t_env *env, t_data *data);
int			ft_env_var_len(char *str, int i);
int			ft_need_to_expand(char *str);
char		*ft_expand_env_var(char *str, int *i, t_env *env, t_data *data);
void		*ft_expand_question_mark(char *str, int i, t_data *data);
char		*ft_expand_quote(char *str, int *i, t_env *env, t_data *data);
char		*ft_replace_env_var(char *str, int i, char *exp_var, t_data *data);
char		*ft_remove_quotes(char *str, char quote, int pos, t_data *data);
char		*ft_remove_dollar(char *str, int i, t_data *data);
char		**ft_heredoc_prio(char **redir_tab, int size, t_list **new_node,
				t_data *data);
char		*ft_expand_heredoc(char *str, t_env *env, t_data *data);
int			ft_find_env_var(t_env *env, char *var, int var_size);
int			ft_count_nodes(t_list *line);

//------	 LISTS UTILS ------//
t_list		*ft_lst_new_node(char *s, t_data *data);
void		ft_free_list(t_list **line);
void		ft_free_env(t_env *env);
void		ft_lstadd_back(t_list **lst, t_list *new_node);
void		ft_init_data(t_data *data);
t_env		*ft_set_env(char **envp, t_data *data);

//------	 GENERAL UTILS ------//
void		ft_reverse_free(char **tab, int j);
int			ft_count_words(char *cmd);
int			ft_is_redir(char c);
int			ft_is_blank(char c);
int			ft_is_quote(char c);
int			ft_is_env_var(char c);
int			ft_is_xpendable(char c);
int			ft_is_heredoc_xpendable(char c);
char		*ft_extract_quote(char *cmd, int *i, char *str, t_data *data);
char		*ft_extract_str(char *cmd, int *i, char *str, t_data *data);
char		*ft_pathcpy(char s[PATH_MAX], char *src, int size);
void		*ft_set_error(t_data *data, int n);
void		ft_error_manager(t_data *data, t_list **line, t_env *env);
void		ft_free_and_exit(t_list *line, t_env *env);
void		ft_free_tab(char **tab);
int			ft_find_word(char *s, char *word);
void		ft_close_fds(t_data *data, int i);

//------	 EXEC UTILS ------//
int			ft_exec_cmd(t_list *line, t_data *data);
int			ft_test_path(t_list *line);
int			ft_fill_pathnames(t_data *data, t_list *line);
int			ft_pars_env(t_data *data);
char		**ft_convert_env(t_data *data);
int			ft_wait_pid(t_data *data);
int			ft_is_builtin(t_list *line, t_data *data);
int			ft_open_redir(t_list *line, t_hdoc *infos, t_data *data);
int			ft_exec_infiles(t_list *line);
int			ft_last_infile(t_list *line, int nb_redir);

#endif
