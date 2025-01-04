/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/01/04 01:09:37 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_cque_tu_veux(t_global *global, char **env)
{
	memset(global, 0, sizeof(t_global));
	global->my_env = ft_taken_to_env(env);
	if (!global->my_env)
		return (1);
	return (0);
}

void	minishell(t_global *global)
{
	t_taken	*taken;
	t_cmd	*cmd;
	char	*rd;

	while (1)
	{
		rd = readline("Mouninashell :");
		add_history(rd);
		taken = ft_initaken(rd);
		if (taken == NULL)
		{
			ft_putendl_fd("Error", 2);
			continue ;
		}
		cmd = ft_parse_lst_taken(taken);
		if (cmd == NULL)
		{
			ft_putendl_fd("Error Parsing", 2);
			continue ;
		}
	}
	ft_free_lst(&taken);
}

int	main(int ac, char **av, char **env)
{
	char		*rd;
	t_global	global;

	if (ac > 1)
		return (1);
	init_cque_tu_veux(&global, env);
	minishell(&global);
	return (0);
}
