#include "../../minishell.h"

void	ft_exec(t_cmd *cmd, t_global *global)
{
	char	*path;
	char	**env;

	// etape 1 ouvrir les fichier 
	ft_open_files(cmd);
	// etape 2 verifier les chemin
	path = ft_pathfinder(cmd, global);
	if (!path)
		return (perror(cmd->arg_cmd[0]), exit(127));		// free
	// etape 3 execve
	env = ft_put_env2d(global);
	if (!env)
		return (ft_putendl_fd("Error env", 2), exit(127));	// free
	if (execve(path, cmd->arg_cmd, env) == -1)
	{
		perror(cmd->arg_cmd[0]);
		ft_free2d(env);
		ft_free2d(cmd->arg_cmd);
		free(path);
		//	free
		exit(1);
	}
}

void	ft_one_command(t_cmd *cmd, t_global *global, t_taken *taken)
{
	pid_t	pid;
	int		status;

	// if (ft_isbulding(cmd->arg_cmd) == true)
	// {
	// 	//do bulding
	// }
	// else
	// {
	pid = ft_fork();
	if (pid == 0)
	{
		ft_exec(cmd, global);
	}
	waitpid(pid, &global->status, 0);
	// }
}

void	ft_explore_ast(t_cmd *node, t_global *global, t_taken *taken)
{
	if (node->type == AND)
		ft_isand(node, global, taken);
	else if (node->type == OR)
		ft_isor(node, global, taken);
	else if (node->type == PIPE)
		ft_ispipe(node, global, taken);
	else if (node->type == CMD)
		ft_isword(node, global, taken);
}

void	ft_execution(t_cmd *cmd, t_global *global, t_taken *taken)
{
	cmd = ft_ast(cmd);
	if (cmd->type == CMD)
	{
		ft_one_command(cmd, global, taken);
	}
	else
		ft_explore_ast(cmd, global, taken);
}

// void	ft_exec_command(t_cmd *command, t_global *emv)
// {
// 	ft_pathfinder();

// }

