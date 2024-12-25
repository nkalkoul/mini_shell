/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/24 18:59:50 by modavid          ###   ########.fr       */
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
# define FILES 4

typedef struct s_taken
{
	char			*token;
	int				type;
	struct s_taken	*next;
}					t_taken;

typedef struct s_data
{
	char	**env;
}			t_data;

typedef struct s_cmd
{
	char			**arg_cmd;
	char			*redir;
	char			*pipe;
	char			*files;
	struct s_cmd	*next;
}					t_cmd;

		// FONCTION DE TOKEN
int		ft_parse_rd(char *rd);
int		ft_parse_operator(char *rd);
void	ft_initaken(t_taken **taken, char *rd, t_cmd **cmd);
void	ft_printaken(t_taken *taken);
void	ft_lstbackadd(t_taken **lst, t_taken *new);
void	ft_printcmd(t_cmd *cmd);

		// FONCTION DE IF
int		ft_space(char c);
int		ft_isquote(char c);
int		ft_isoperator(char c);
int		ft_isredir(char c);

#endif
