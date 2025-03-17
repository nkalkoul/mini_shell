/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 22:07:04 by modavid          ###   ########.fr       */
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

void	minishell_bis(t_global *global, char *rd)
{
	char	*nrd;
	t_cmd	*cmd;

	nrd = ft_strdup(rd);
	free(rd);
	rd = nrd;
	if (rd[0] == '\0')
		return ;
	add_history(rd);
	cmd = ft_parsing(global, rd);
	if (!cmd)
		return ;
	ft_execution(cmd, global);
	ft_clearbag(NULL);
}

void	minishell(t_global *global)
{
	char	*rd;

	while (1)
	{
		ft_signal_for_parent();
		rd = readline("\001\033[34m\002mouninashell: \001\033[0m\002");
		global->ext = 0;
		if (g_sign != 0)
		{
			ft_reset_signal(global);
			ft_clearbag(NULL);
			free(rd);
			continue ;
		}
		if (rd == NULL)
			return (ft_printf(2, "exit\n"), ft_free_and_exit(global->status));
		minishell_bis(global, rd);
		continue ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_global	global;

	if (ac > 1)
		return (1);
	if (isatty(STDIN_FILENO) == 0 || isatty(STDOUT_FILENO) == 0)
	{
		ft_printf(STDOUT_FILENO, "no tty\n");
		return (1);
	}
	if (!av[0])
		return (1);
	if (init_my_env(&global, env) == 1)
		return (1);
	minishell(&global);
	return (0);
}
