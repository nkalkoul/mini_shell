/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/15 15:18:11 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_sign = 0;

int	init_my_env(t_global *global, char **env)
{
	ft_memset(global, 0, sizeof(t_global));
	global->my_env = ft_take_myenv(env, global);
	if (!global->my_env)
		return (1);
	return (0);
}

t_cmd	*ft_parsing(t_global *global, char *rd)
{
	t_taken	*taken;
	t_cmd	*cmd;

	taken = ft_initaken(rd);
	if (!taken)
	{
		ft_clearbag(NULL);
		return (NULL);
	}
	cmd = ft_parse_lst_taken(taken, global);
	if (cmd == NULL)
	{
		ft_clearbag(NULL);
		return (NULL);
	}
	return (cmd);
}

void	minishell(t_global *global)
{
	t_cmd	*cmd;
	char	*rd;
	char	*nrd;

	while (1)
	{
		ft_signal_for_parent();
		rd = readline("mouninashell ");
		if (g_sign != 0)
		{
			global->status = g_sign;
			g_sign = 0;
			ft_clearbag(NULL);
			free(rd);
			continue ;
		}
		if (rd == NULL)
			return (ft_free_and_exit(global->status));
		nrd = ft_strdup(rd);
		free(rd);
		rd = nrd;
		if (rd[0] == '\0')
			continue ;
		add_history(rd);
		cmd = ft_parsing(global, rd);
		if (!cmd)
			continue ;
		ft_execution(cmd, global);
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
