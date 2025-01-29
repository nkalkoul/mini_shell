/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/01/29 01:04:33 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_my_env(t_global *global, char **env)
{
	memset(global, 0, sizeof(t_global));
	global->my_env = ft_take_myenv(env);
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
		if (rd == NULL)
			return ;
		if (rd[0] == '\0')
			continue;
		add_history(rd);
		taken = ft_initaken(rd);
		if (ft_strcmp(taken->token, "exit") == 0)
			exit(0);
		if (taken == NULL || ft_expandables(&taken, global) == 1)
		{
			ft_putendl_fd("Error", 2);
			continue ;
		}
		// if (ft_export(taken) == 0)
		// {
		// 	ft_print_export(global, taken);
		// 	continue ;
		// }
		if (taken == NULL)
			continue;
		cmd = ft_parse_lst_taken(taken);
		ft_free_lst(&taken);
		if (cmd == NULL)
		{
			ft_putendl_fd("Error Parsing", 2);
			continue ;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	char		*rd;
	t_global	global;

	if (ac > 1)
		return (1);
	if (init_my_env(&global, env) == 1)
		return (1);
	minishell(&global);
	return (0);
}
