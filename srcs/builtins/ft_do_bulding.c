#include "../../minishell.h"

int	ft_isbulding(char **command)
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

void	ft_do_bulding(char **cmd, t_global *global)
{
	if (ft_strcmp(cmd[0], "exit") == 0)
		global->status = ft_exit(cmd, global);
	else if (ft_strcmp(cmd[0], "env") == 0)
		global->status = ft_printenv(cmd, global);
	else if (ft_strcmp(cmd[0], "export") == 0)
		global->status = ft_print_export(cmd, global);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		global->status = ft_unset(cmd, global);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		global->status = ft_echo(cmd, global);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		global->status = ft_pwd(global);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		global->status = ft_cd(cmd, global);
}
