/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:16:33 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/01 11:52:34 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_is_fork(t_cmd *node, t_global *global)
{
	pid_t	pid;
	
	if (node->type == WORD && ft_isbulding(node->arg_cmd) == false)
	{
		pid = ft_fork();
		if (pid == 0)
		ft_explore_ast(node, global);
		waitpid(pid, &global->status, 0);
	}
	else
	ft_explore_ast(node, global);
}

void	ft_isor(t_cmd *node, t_global *global)
{
	check_is_fork(node->left, global);
	if (global->status == 0)
		return ;
	ft_explore_ast(node->right, global);
}

void	ft_isand(t_cmd *node, t_global *global)
{
	check_is_fork(node, global);
	if (global->status == 0)
		ft_explore_ast(node->right, global);
}

void	ft_isword(t_cmd *node, t_global *global)
{
	if (ft_isbulding(node->arg_cmd) == true)
	{
		//execbulding
	}
	else
		ft_exec(node, global);
}

void	ft_ispipe(t_cmd *node, t_global *global)
{
	int	fd[2];
	int	pidleft;
	int	pidright;
	int	status;

	ft_pipe(fd);
	pidleft = ft_fork();
	if (pidleft == 0)
	{
		close(fd[0]);
		ft_dup2(fd[1], STDOUT_FILENO);
		ft_explore_ast(node->left, global);
	}
	pidright = fork();
	if (pidright == 0)
	{
		close(fd[1]);
		ft_dup2(fd[0], STDIN_FILENO);
		ft_explore_ast(node->right, global);
	}
	(close(fd[0]), close(fd[1]));
	waitpid(pidleft, &status, 0);
	waitpid(pidright, &status, 0);
}

void	ft_dup2(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}
