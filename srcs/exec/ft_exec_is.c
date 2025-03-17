/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:16:33 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 15:34:43 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_is_fork(t_cmd *node, t_global *global)
{
	pid_t	pid;

	if (node->type == CMD && ft_isbulding(node->arg_cmd) == false)
	{
		pid = ft_fork(global);
		if (pid == 0)
			ft_explore_ast(node, global);
		ft_waitpid(pid, global, 0);
	}
	else
		ft_explore_ast(node, global);
}

void	ft_isor(t_cmd *node, t_global *global)
{
	check_is_fork(node->left, global);
	if (global->status == 0 || global->status == 128 + SIGINT)
		return ;
	if (global->status == 128 + SIGQUIT)
		ft_if_signal(global);
	check_is_fork(node->right, global);
}

void	ft_isand(t_cmd *node, t_global *global)
{
	check_is_fork(node->left, global);
	if (global->status == 0)
		check_is_fork(node->right, global);
}

void	ft_isword(t_cmd *node, t_global *global)
{
	int		fd[2];

	if (ft_verif(node) == 1)
		return ;
	ft_expandables(node, global);
	if (ft_isbulding(node->arg_cmd) == true)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (ft_open_files(node) == 1)
		{
			(close(fd[0]), close(fd[1]));
			ft_free_and_exit(1);
		}
		ft_do_bulding(node->arg_cmd, global);
		ft_dup2(fd[0], STDIN_FILENO);
		ft_dup2(fd[1], STDOUT_FILENO);
	}
	else
		ft_exec(node, global);
}

void	ft_ispipe(t_cmd *node, t_global *global)
{
	int	fd[2];
	int	pidleft;
	int	pidright;

	ft_pipe(fd);
	pidleft = ft_fork(global);
	if (pidleft == 0)
	{
		close(fd[0]);
		ft_dup2(fd[1], STDOUT_FILENO);
		ft_explore_ast(node->left, global);
		ft_free_and_exit(0);
	}
	pidright = ft_fork(global);
	if (pidright == 0)
	{
		close(fd[1]);
		ft_dup2(fd[0], STDIN_FILENO);
		ft_explore_ast(node->right, global);
		ft_free_and_exit(0);
	}
	(close(fd[0]), close(fd[1]));
	ft_waitpid(pidleft, global, 0);
	ft_waitpid(pidright, global, 0);
}
