/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/10 10:36:43 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_my_env(t_global *global, char **env)
{
	ft_memset(global, 0, sizeof(t_global));
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
		rd = readline("Mouninashell ");
		if (rd == NULL)
			return (ft_free_and_exit(1));
		if (ft_strcmp("exit", rd) == 0)
		{
			ft_free((void *) -1);
			exit(0);
		}
		if (rd[0] == '\0')
			continue ;
		add_history(rd);
		taken = ft_initaken(rd);
		if (!taken)
		{
			ft_clearbag(NULL);
			continue ;
		}
		cmd = ft_parse_lst_taken(taken);
		if (cmd == NULL || ft_expandables(cmd, global) == 1)
		{
			ft_putendl_fd("Error Parsing\n", 2);
			ft_clearbag(NULL);
			continue ;
		}
		ft_execution(cmd, global, taken);
		ft_clearbag(NULL);
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
