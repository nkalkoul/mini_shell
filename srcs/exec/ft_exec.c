/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:34 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:14:06 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exec(t_cmd *cmd, t_global *global)
{
	char	*path;
	char	**env;

	ft_open_files(cmd);
	path = ft_pathfinder(cmd, global);
	if (!path)
		return (perror(cmd->arg_cmd[0]), ft_free_and_exit(127));
	env = ft_put_env2d(global);
	if (!env)
		return (ft_putendl_fd("Error env", 2), ft_free_and_exit(127));
	if (execve(path, cmd->arg_cmd, env) == -1)
	{
		perror(cmd->arg_cmd[0]);
		ft_free_and_exit(2);
	}
}

int	ft_one_command_bis(int *fd, t_cmd *cmd, t_global *global)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	if (ft_open_files(cmd) == 1)
	{
		(close(fd[0]), close(fd[1]));
		return (1);
	}
	ft_do_bulding(cmd->arg_cmd, global);
	ft_dup2(fd[0], STDIN_FILENO);
	ft_dup2(fd[1], STDOUT_FILENO);
	return (0);
}

void	ft_one_command(t_cmd *cmd, t_global *global)
{
	pid_t	pid;
	int		fd[2];

	if (ft_verif(cmd) == 1)
	{
		global->status = 1;
		return ;
	}
	ft_expandables(cmd, global);
	if (ft_isbulding(cmd->arg_cmd) == true)
	{
		if (ft_one_command_bis(fd, cmd, global) == 1)
			return ;
	}
	else
	{
		pid = ft_fork(global);
		if (pid == 0)
			ft_exec(cmd, global);
		ft_waitpid(pid, global, 0);
	}
}

void	ft_explore_ast(t_cmd *node, t_global *global)
{
	if (node->type == AND)
		ft_isand(node, global);
	else if (node->type == OR)
		ft_isor(node, global);
	else if (node->type == PIPE)
		ft_ispipe(node, global);
	else if (node->type == CMD)
		ft_isword(node, global);
}

void	ft_execution(t_cmd *cmd, t_global *global)
{
	ft_signal_for_exec();
	cmd = ft_ast(cmd);
	if (cmd->type == CMD)
		ft_one_command(cmd, global);
	else
		ft_explore_ast(cmd, global);
	ft_if_signal(global);
}
