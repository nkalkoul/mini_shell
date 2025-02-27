#include "../../minishell.h"

int	ft_isbulsing(char **command)
{
	if (ft_strcmp(command[0], "exit") == 0)
		return (true);
	if (ft_strcmp(command[0], "env") == 0)
		return (true);
	if (ft_strcmp(command[0], "export") == 0)
		return (true);
	if (ft_strcmp(command[0], "unset") == 0)
		return (true);
	if (ft_strcmp(command[0], "echo") == 0)
		return (true);
	if (ft_strcmp(command[0], "pwd") == 0)
		return (true);
	if (ft_strcmp(command[0], "cd") == 0)
		return (true);
	return (false);
}

void	ft_open_redirD(t_files *files)
{
	int	fd;

	fd = open(files->path, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	if (fd == -1)
	{
		perror(files->path);
	}
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
		else if (files->type == REDIRG)
		else if (files->type == REDIRGG)
		files = files->next;
	}
}

void	ft_exec(t_cmd *cmd, t_global *global)
{
	// etape 1 ouvrir les fichier 

	// etape 2 verifier les chemin

	// etape 3 execve
}

void	ft_one_command(t_cmd *cmd, t_global *global)
{
	pid_t	pid;
	int		status;

	if (ft_isbulding(cmd->arg_cmd) == true)
	{
		//do bulding
	}
	else
	{
		pid = ft_fork();
		if (pid == 0)
		{
			ft_exec(cmd, global);
		}
		waitpid(pid, &status, 0);
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
	else if (node->type == WORD)
		ft_isword(node, global);
}

void	ft_execution(t_cmd *cmd, t_global *global)
{
	cmd = ft_ast(cmd);
	if (cmd->type == WORD)
	{
		ft_one_command(cmd, global);
	}
	else
		ft_explore_ast(cmd, global);
}

void	ft_exec_command(t_cmd *command, t_global *emv)
{
	ft_pathfinder();

}

