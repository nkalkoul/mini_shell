/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:10:44 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/02/26 01:24:43 by nkalkoul         ###   ########.fr       */
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
	return (pid);
}
