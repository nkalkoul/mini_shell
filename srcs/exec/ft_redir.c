/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:42 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:07:43 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_open_redirgg(t_files *files)
{
	int		i;
	char	**finalred;
	int		fd[2];

	i = 0;
	finalred = files->heredoc_content;
	if (finalred == NULL)
		return ;
	ft_pipe(fd);
	while (finalred[i])
	{
		ft_putendl_fd(finalred[i], fd[1]);
		i++;
	}
	ft_dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}

int	ft_open_redirg(t_files *files)
{
	int	fd;

	fd = open(files->path, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror(files->path);
		return (1);
	}
	ft_dup2(fd, STDIN_FILENO);
	return (0);
}

int	ft_open_redirdd(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(files->path);
		return (1);
	}
	ft_dup2(fd, STDOUT_FILENO);
	return (0);
}

int	ft_open_redird(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(files->path);
		return (1);
	}
	ft_dup2(fd, STDOUT_FILENO);
	return (0);
}

int	ft_open_files(t_cmd *cmd)
{
	t_files	*files;

	files = cmd->files;
	while (files)
	{
		if (files->type == REDIRD && ft_open_redird(files) == 1)
			return (1);
		else if (files->type == REDIRDD && ft_open_redirdd(files) == 1)
			return (1);
		else if (files->type == REDIRG && ft_open_redirg(files) == 1)
			return (1);
		else if (files->type == REDIRGG)
			ft_open_redirgg(files);
		files = files->next;
	}
	return (0);
}
