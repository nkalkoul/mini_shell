#include "../../minishell.h"

char	**ft_addtab(char **tab, char *red)
{
	char	**new;
	int		i;

	i = 0;
	if (!tab)
	{
		tab = ft_malloc(sizeof(char *) * 1);
		tab[0] = 0;
	}
	new = ft_malloc(sizeof(char *) * (ft_countdouble(tab) + 2));
	if (!new)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = ft_strdup(red);
	new[++i] = 0;
	return (new);
}

char	**ft_newread(t_files *files)
{
	char	**redir;
	char	*red;
	int		i;

	i = 0;
	redir = NULL;
	while (1)
	{
		red = readline("> ");
		if (ft_strcmp(files->path, red) == 0)
			break ;
		redir = ft_addtab(redir, red);
		if (redir == NULL)
			return (NULL);
	}
	return (redir);
}

void	ft_open_redirGG(t_files *files)
{
	int		i;
	char	**finalred;
	int		fd[2];

	finalred = ft_newread(files);
	if (finalred == NULL)
		return ;
	ft_pipe(fd);
	while (finalred[i])
	{
		
	}
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
