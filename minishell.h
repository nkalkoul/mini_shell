/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:11:23 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/18 23:51:54 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H

# define MINI_SHELL_H
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_taken
{
    char            *token;
    int             index;
    int             type;
    struct s_taken  *next;
}                   t_taken;

typedef struct s_data
{
    char    **env;
}           t_data;

typedef struct  s_cmd
{
	char			**cmd;
	int				index;
	struct s_cmd	*next;
}					t_cmd;

void	ft_initaken(t_taken *taken, char *rd);

#endif
