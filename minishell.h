/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/01/01 19:57:10 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define WORD 1
# define PIPE 2
# define REDIR 3

typedef struct s_taken
{
	char			*token;
	int				type;
	struct s_taken	*next;
}					t_taken;

typedef struct s_files
{
	char			*redir;
	char			*path;
	struct s_files	*next;
}					t_files;

typedef struct s_cmd
{
	char			**arg_cmd;
	struct s_files	*files;
	struct s_cmd	*next;
}					t_cmd;

		// FONCTION DE TOKEN
int		ft_parse_rd(char *rd);
int		ft_parse_operator(char *rd);
int		ft_initaken(t_taken **taken, char *rd);
void	ft_printaken(t_taken *taken);
void	ft_lstbackadd(t_taken **lst, t_taken *new);
void	ft_printcmd(t_cmd *cmd);
void	ft_printfiles(t_files *files);
int		ft_parse_lst_taken(t_taken **taken, t_cmd **cmd, t_files **files);
void	ft_lstbackadd_files(t_files **lst, t_files *new);
void	ft_lstbackadd_cmd(t_cmd **lst, t_cmd *new);

		// FONCTION DE IF
int		ft_space(char c);
int		ft_isquote(char c);
int		ft_isoperator(char c);
int		ft_isredir(char c);

		// FONCTION DE UTILS
void	ft_free_lst(t_taken **taken);

#endif
