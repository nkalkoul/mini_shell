/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/21 20:08:54 by modavid          ###   ########.fr       */
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
	int				index;
	int				type;
	struct s_taken	*next;
}					t_taken;

typedef struct s_data
{
	char	**env;
}			t_data;

typedef struct s_cmd
{
	char			**cmd;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

void	ft_initaken(t_taken **taken, char *rd);
int		ft_parse_rd(char *rd);

#endif
