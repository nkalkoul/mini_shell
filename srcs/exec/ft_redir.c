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
	printf("\n%s", files->path);
	while (1)
	{
		printf(" slor");
		red = readline("> ");
		if (ft_strcmp(files->path, red) == 0)
			break ;
		printf(" old el");
		redir = ft_addtab(redir, red);
		printf("\n%s", redir[0]);
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

	i = 0;
	printf("je sui la\n");
	finalred = ft_newread(files);
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
	int		i;

	i = 0;
	files = cmd->files;
	while (files)
	{
		printf("%d ", i++);
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
