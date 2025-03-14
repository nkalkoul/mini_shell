/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:10:44 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/15 08:18:42 by modavid          ###   ########.fr       */
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

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_free(((void *) -1));
		(perror("FORK"), exit(-1));
	}
	if (pid == 0)
		ft_signal_for_child();
	return (pid);
}

void	ft_dup2(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	ft_waitpid(int pid, int *status, int options)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = 128 + WTERMSIG(*status);
}
