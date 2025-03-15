/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 08:31:55 by nas91             #+#    #+#             */
/*   Updated: 2025/03/15 10:50:26 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isoperator(char c)
{
	if (c == '|' || ft_isredir(c) == 1)
		return (1);
	return (0);
}

int	ft_verif(t_cmd *cmd)
{
	int	fd[2];

	if (cmd->arg_cmd == NULL && cmd->files)
	{
		fd[0] = dup(STDIN_FILENO);
		fd[1] = dup(STDOUT_FILENO);
		if (ft_open_files(cmd) == 1)
		{
			(close(fd[0]), close(fd[1]));
			return (1);
		}
		ft_dup2(fd[0], STDIN_FILENO);
		ft_dup2(fd[1], STDOUT_FILENO);
		return (1);
	}
	return (0);
}
