/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/02 08:24:45 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/wait.h>

# define CMD 0
# define WORD 1
# define PIPE 2
# define REDIRD 3
# define REDIRG 6
# define REDIRDD 7
# define REDIRGG 8
# define OR 4
# define AND 5

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;	
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
}	t_global;

		// FONCTION DE TOKEN
int		ft_parse_rd(char *rd);
int		ft_parse_quote(char *rd);
int		ft_parse_operator(char *rd);
t_taken	*ft_initaken(char *rd);
void	ft_lstbackadd(t_taken **lst, t_taken *new);
t_cmd	*ft_parse_lst_taken(t_taken *taken);
void	ft_lstbackadd_files(t_files **lst, t_files *new);
void	ft_lstbackadd_cmd(t_cmd **lst, t_cmd *new);
t_env	*ft_take_myenv(char **env);
void	ft_lstbackadd_env(t_env **lst, t_env *new);
int		ft_expandables(t_taken **taken, t_global *global);
char	*ft_getenv(char *key, t_global *global);
int		ft_expand_token(t_taken	*current, t_global *global);
int		ft_expand_simple(char *token, char quote, int i);

		// FONCTION DE PRINT
void	ft_printaken(t_taken *taken);
void	ft_printcmd(t_cmd *cmd);
void	ft_printfiles(t_cmd *cmd);
void	ft_printenv(t_env *my_env);

		// FONCTION DE BUILTINS
void	ft_print_export(t_global *global);
int		ft_export_node(t_taken *taken, t_global *global);
void	ft_unset(t_taken *taken, t_global *global);
void	ft_echo(t_taken *taken);
int		ft_pwd(t_global *global);
int		ft_cd(t_taken *taken);

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

		// FONCTION DE GARBAGE
void	*ft_malloc(long int l);
int		ft_lstbackadd_garbage(void *ptr, t_garbage_head *garbage);
void	ft_killnode(t_garbage_head *garbage, void *ptr);
void	ft_finishbag(t_garbage_head *garbage);
void	ft_free(void *ptr);

		// EXEC
t_cmd	*ft_ast(t_cmd *first);
pid_t	ft_fork(void);
void	ft_isor(t_cmd *node, t_global *global, t_taken *taken);
void	ft_isand(t_cmd *node, t_global *global, t_taken *taken);
void	ft_isword(t_cmd *node, t_global *global, t_taken *taken);
int		*ft_pipe(int *fd);
void	ft_explore_ast(t_cmd *node, t_global *global, t_taken *taken);

#endif
