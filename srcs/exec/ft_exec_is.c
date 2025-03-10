/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:16:33 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/10 11:50:35 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_is_fork(t_cmd *node, t_global *global, t_taken *taken)
{
	pid_t	pid;

	if (node->type == CMD && ft_isbulding(node->arg_cmd) == false)
	{
		pid = ft_fork();
		if (pid == 0)
			ft_explore_ast(node, global, taken);
		waitpid(pid, &global->status, 0);
	}
	else
		ft_explore_ast(node, global, taken);
}

void	ft_isor(t_cmd *node, t_global *global, t_taken *taken)
{
	pid_t	pid;

	check_is_fork(node->left, global, taken);
	if (global->status == 0)
		return ;
	check_is_fork(node->right, global, taken);
}

void	ft_isand(t_cmd *node, t_global *global, t_taken *taken)
{
	pid_t	pid;

	check_is_fork(node->left, global, taken);
	if (global->status == 0)
		check_is_fork(node->right, global, taken);
}

void	ft_isword(t_cmd *node, t_global *global, t_taken *taken)
{
	if (ft_isbulding(node->arg_cmd) == true)
		ft_do_bulding(node->arg_cmd, global);
	else
		ft_exec(node, global);
}

void	ft_ispipe(t_cmd *node, t_global *global, t_taken *taken)
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
		ft_explore_ast(node->left, global, taken);
		ft_free_and_exit(0);
	}
	pidright = ft_fork();
	if (pidright == 0)
	{
		close(fd[1]);
		ft_dup2(fd[0], STDIN_FILENO);
		ft_explore_ast(node->right, global, taken);
		ft_free_and_exit(0);
	}
	(close(fd[0]), close(fd[1]));
	waitpid(pidleft, &global->status, 0);
	waitpid(pidright, &global->status, 0);
}
