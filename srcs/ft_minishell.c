/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/02/09 18:09:51 by modavid          ###   ########.fr       */
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
			continue ;
		add_history(rd);
		taken = ft_initaken(rd);
		if (!taken)
			continue ;
		if (ft_strcmp(taken->token, "exit") == 0)
			(exit(0));				/*ft_free(((void *) -1)),*/
		if (taken == NULL || ft_expandables(&taken, global) == 1)
		{
			ft_putendl_fd("Error", 2);
			// ft_free(((void *) -1));
			continue ;
		}
		if (!taken->next && ft_strcmp(taken->token, "env") == 0)
		{
			ft_printenv(global->my_env);
			continue ;
		}
		if (ft_strcmp(taken->token, "export") == 0)
		{
			if (taken->next == NULL)
				ft_print_export(global);
			else
			{
				if (ft_export_node(taken, global) == 1)
					ft_putendl_fd("Error", 2);   // free
			}
			continue ;
		}
		// ft_print_export(global, taken);
		if (taken->next && ft_strcmp(taken->token, "unset") == 0)
		{
			ft_unset(taken, global);
			continue ;
		}
		if (ft_strcmp(taken->token, "echo") == 0)
		{
			ft_echo(taken);
			continue ;
		}
		if (ft_strcmp(taken->token, "pwd") == 0)
		{
			if (ft_pwd(global) == 1)
				ft_putendl_fd("Error", 2);    // free
			continue ;
		}
		// if (taken == NULL)
		// 	continue ;
		cmd = ft_parse_lst_taken(taken);
		if (cmd == NULL)
		{
			ft_putendl_fd("Error Parsing", 2);
			// ft_free(((void *) -1));
			continue ;
		}
		// ft_free(((void *) -1));
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
