/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:08:09 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 13:26:35 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_ctc(int sig)
{
	if (sig == SIGINT)
	{
		g_sign = 128 + sig;
		rl_done = 1;
	}
}

int	ft_event(void)
{
	return (0);
}

void	ft_signal_for_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
}

void	ft_signal_for_parent(void)
{
	rl_event_hook = ft_event;
	signal(SIGINT, ft_ctc);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_if_signal(t_global *glob)
{
	if (glob->status == 128 + SIGINT)
		ft_putendl_fd("", 2);
	if (glob->status == 128 + SIGQUIT)
		ft_putendl_fd("Quit (core dumped)", 2);
}
