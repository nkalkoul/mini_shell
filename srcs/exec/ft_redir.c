#include "../../minishell.h"

char	**ft_newread(t_files *files)
{
	char	*redir;
	char	*red;

	redir = ft_strdup("");
	if (redir == NULL)
		return ;
	while (1)
	{
		red = readline(">");
		if (red == files->path)
			break ;
		redir = ft_re_strjoin(redir, red);
		redir = ft_re_strjoin(redir, "\n");
		if (redir == NULL)
			return (NULL);
	}
	return (ft_split(redir, '\n'));
}

void	ft_open_redirGG(t_files *files)
{
	int		i;
	char	**finalred;

	finalred = ft_newread(files);
	if (finalred == NULL)
		return ;
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
	t_files	*files;

	files = cmd->files;
	while (files)
	{
		if (files->type == REDIRD)
			ft_open_redirD(files);
		else if (files->type == REDIRDD)
			ft_open_redirDD(files);
		else if (files->type == REDIRG)
			ft_open_redirG(files);
		else if (files->type == REDIRGG)
			ft_open_redirGG(files);
		files = files->next;
	}
}
