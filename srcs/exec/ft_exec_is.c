/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:16:33 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/13 17:54:05 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_waitpid(int pid, int *status, int options)
{
	waitpid(pid, status, 0);
	if (WIFEXITED(*status))
		*status = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		*status = 128 + WTERMSIG(*status);
}

void	check_is_fork(t_cmd *node, t_global *global, t_taken *taken)
{
	pid_t	pid;

	if (node->type == CMD && ft_isbulding(node->arg_cmd) == false)
	{
		pid = ft_fork();
		if (pid == 0)
			ft_explore_ast(node, global, taken);
		ft_waitpid(pid, &global->status, 0);
	}
	else
		ft_explore_ast(node, global, taken);
}

void	ft_isor(t_cmd *node, t_global *global, t_taken *taken)
{
	pid_t	pid;

	check_is_fork(node->left, global, taken);
	if (global->status == 0 || global->status == 128 + SIGINT)
		return ;
	if (global->status == 128 + SIGQUIT)
		ft_if_signal(global);
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
	int		fd[2];

	ft_expandables(node, global);
	if (ft_isbulding(node->arg_cmd) == true)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		ft_open_files(node);
		ft_do_bulding(node->arg_cmd, global);
		ft_dup2(fd[0], STDIN_FILENO);
		ft_dup2(fd[1], STDOUT_FILENO);
	}
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
	ft_waitpid(pidleft, &global->status, 0);
	ft_waitpid(pidright, &global->status, 0);
}
