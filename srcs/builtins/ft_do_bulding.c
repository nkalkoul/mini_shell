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

void ft_do_bulding(t_taken *taken, t_global *global)
{
	if (ft_strcmp(taken->token, "exit") == 0)
		return (true);
	if (ft_strcmp(taken->token, "env") == 0)
		global->status = ft_printenv(taken, global);
	else if (ft_strcmp(taken->token, "export") == 0)
		global->status = ft_print_export(taken, global);
	else if (ft_strcmp(taken->token, "unset") == 0)
		global->status = ft_unset(taken, global);
	else if (ft_strcmp(taken->token, "echo") == 0)
		global->status = ft_echo(taken);
	else if (ft_strcmp(taken->token, "pwd") == 0)
		global->status = ft_pwd(global);
	else if (ft_strcmp(taken->token, "cd") == 0)
		global->status = ft_cd(taken, global);
}
