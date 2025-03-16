/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:16:22 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 12:02:40 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_count_key(char *env)
{
	int	j;

	j = 0;
	while (env[j] != '=')
		j++;
	return (j);
}

int	ft_count_value(char *env, int j)
{
	while (env[j] != '\0')
		j++;
	return (j - 1);
}

int	ft_isimple(char rd)
{
	if (rd == '\'')
		return (0);
	return (1);
}

int	ft_isdouble(char rd)
{
	if (rd == '"')
		return (0);
	return (1);
}
