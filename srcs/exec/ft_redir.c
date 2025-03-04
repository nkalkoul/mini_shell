#include "../../minishell.h"

void	ft_open_redirGG(t_files *files)
{
	int	i;
}

void	ft_open_redirG(t_files *files)
{
	int	fd;

	fd = open(files->path, O_RDONLY, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	ft_open_redirDD(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_redirD(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(files->path);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	ft_open_files(t_cmd *cmd)
{
	t_files *files;

	files = cmd->files;
	while (files)
	{
		if (files->type == REDIRD)
			ft_open_redirD(files);
		else if (files->type == REDIRDD)
			ft_open_redirDD(files);
		else if (files->type == REDIRG)
			ft_open_redirG(files);
		// else if (files->type == REDIRGG)
		// 	ft_open_redirGG(files);
		files = files->next;
	}
}
