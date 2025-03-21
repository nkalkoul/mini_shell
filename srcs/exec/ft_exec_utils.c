/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:10:44 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 15:31:22 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	*ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
	{
		ft_free((void *) -1);
		(perror("pipe"), exit(-1));
	}
	return (fd);
}

pid_t	ft_fork(t_global *g)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_free(((void *) -1));
		(perror("FORK"), exit(-1));
	}
	if (pid == 0)
	{
		ft_signal_for_child();
		ft_shlvlup(g);
	}
	return (pid);
}

void	ft_dup2(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	ft_waitpid(int pid, t_global *g, int options)
{
	waitpid(pid, &g->status, options);
	if (WIFEXITED(g->status))
		g->status = WEXITSTATUS(g->status);
	else if (WIFSIGNALED(g->status))
	{
		g->status = 128 + WTERMSIG(g->status);
		g->ext = 1;
	}
}
