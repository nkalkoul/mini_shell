/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 12:03:10 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>

# define CMD 0
# define WORD 1
# define PIPE 2
# define REDIRD 3
# define REDIRG 6
# define REDIRDD 7
# define REDIRGG 8
# define OR 4
# define AND 5

extern volatile __sig_atomic_t	g_sign;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;	
	int					lock;
}	t_garbage;

typedef struct s_garbage_head
{
	struct s_garbage	*head;	
}	t_garbage_head;

typedef struct s_taken
{
	char			*token;
	int				type;
	struct s_taken	*next;
}	t_taken;

typedef struct s_files
{
	int				type;
	char			**heredoc_content;
	char			*path;
	struct s_files	*next;
}	t_files;

typedef struct s_cmd
{
	char			**arg_cmd;
	struct s_files	*files;
	struct s_cmd	*next;
	struct s_cmd	*right;
	struct s_cmd	*left;
	struct s_cmd	*top;
	int				type;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_global
{
	t_env	*my_env;
	int		status;
	char	*pdw;
	int		lvl;
}	t_global;

		// FONCTION DE TOKEN
int		ft_parse_rd(char *rd);
int		ft_parse_quote(char *rd);
int		ft_parse_operator(char *rd);
int		ft_check_error_parse(t_taken *current);
t_taken	*ft_initaken(char *rd);
void	ft_lstbackadd(t_taken **lst, t_taken *new);
t_cmd	*ft_parse_lst_taken(t_taken *taken, t_global *global);
int		ft_token_to_cmd(t_taken **current, t_cmd **cmd, t_global *global);
void	ft_lstbackadd_files(t_files **lst, t_files *new);
void	ft_lstbackadd_cmd(t_cmd **lst, t_cmd *new);
t_env	*ft_take_myenv(char **env, t_global *g);
void	ft_lstbackadd_env(t_env **lst, t_env *new);
int		ft_expandables(t_cmd *cmd, t_global *global);
char	*ft_getenv(char *key, t_global *global);
char	*ft_expand_token(char *arg, t_global *global);
char	*add_env_variable(char *token, int *i, char *result, t_global *global);
char	*add_other_chars(char *token, int *i, char *result, char *set);
char	*add_double_quotes(char *token, int *i, char *result, t_global *global);
char	*add_simple_quotes(char *token, int *i, char *result);

		// FONCTION DE PRINT
void	ft_printaken(t_taken *taken);
void	ft_printcmd(t_cmd *cmd);
void	ft_printfiles(t_cmd *cmd);

		// FONCTION DE BUILTINS
int		ft_printenv(char **cmd, t_global *global);
int		ft_print_export(char **cmd, t_global *global);
void	ft_export_node(char **cmd, t_global *global);
void	ft_replace_node(t_env *tmp, t_env *prev, t_global *global);
int		ft_unset(char **cmd, t_global *global);
int		ft_echo(char **cmd, t_global *global);
int		ft_pwd(t_global *global);
char	*ft_pwd2(void);
int		ft_cd(char **cmd, t_global *global);
int		ft_isbulding(char **command);
void	ft_do_bulding(char **cmd, t_global *global);
int		ft_exit(char **cmd, t_global *global);

		// FONCTION DE IF
int		ft_space(char c);
int		ft_isquote(char c);
int		ft_isoperator(char c);
int		ft_isredir(char c);

		// FONCTION DE UTILS
void	ft_free_lst(t_taken **taken);
void	ft_free_files(t_files **files);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free2d(char **str);
void	ft_free_env(t_env *my_env);
void	ft_free_and_exit(int status);
int		ft_verif(t_cmd *cmd);
void	ft_shlvlup(t_global *g);
int		ft_count_key(char *env);
int		ft_count_value(char *env, int j);
void	ft_errormsg(int m);
int		ft_isimple(char rd);
int		ft_isdouble(char rd);

		// FONCTION DE GARBAGE
void	*ft_malloc(long int l);
int		ft_lstbackadd_garbage(void *ptr, t_garbage_head *garbage);
void	ft_killnode(t_garbage_head *garbage, void *ptr);
void	ft_finishbag(t_garbage_head *garbage);
void	ft_free(void *ptr);
void	ft_locks(void *ptr, t_garbage_head *garb);
void	ft_unlocks(void *ptr, t_garbage_head *garb);
void	ft_clearbag(t_garbage_head *garb);

		// EXEC
t_cmd	*ft_ast(t_cmd *first);
pid_t	ft_fork(t_global *g);
void	ft_ispipe(t_cmd *node, t_global *global);
void	ft_isor(t_cmd *node, t_global *global);
void	ft_isand(t_cmd *node, t_global *global);
void	ft_isword(t_cmd *node, t_global *global);
int		*ft_pipe(int *fd);
void	ft_explore_ast(t_cmd *node, t_global *global);
int		ft_open_files(t_cmd *cmd);
char	**ft_put_env2d(t_global *global);
char	*ft_pathfinder(t_cmd *cmd, t_global *global);
void	ft_execution(t_cmd *cmd, t_global *global);
void	ft_exec(t_cmd *cmd, t_global *global);
void	ft_dup2(int fd1, int fd2);
char	**ft_newread(t_files *files, t_global *g);
void	ft_waitpid(int pid, int *status, int options);

		// SIGNAL
void	ft_signal_for_parent(void);
void	ft_signal_for_child(void);
void	ft_if_signal(t_global *glob);
void	ft_signal_for_exec(void);

#endif
