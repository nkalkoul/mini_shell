/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_is.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 01:16:33 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/02/26 02:24:55 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_isor(t_cmd *node, t_global *global)
{
	ft_explore_ast(node->left, global);
	//checker si la gauche a rater, si sa a rater : faire la droite
	ft_explore_ast(node->right, global);
	// else quitter instantanemment

}

void	ft_isand(t_cmd *node, t_global *global)
{
	ft_explore_ast(node->left, global);
	// if sa a reussi
	ft_explore_ast(node->right, global);
	// if sa a rater ENDGAME FREEE DOOMSDAY AGE OF ULTRON

}

void	ft_isword(t_cmd *node, t_global *global)
{
	if (ft_isbulsing(node->arg_cmd) == true)
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
	waitpid(pidleft, &status, 0);
	waitpid(pidright, &status, 0);
}

void	ft_dup2(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}
