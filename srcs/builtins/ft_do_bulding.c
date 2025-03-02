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

int ft_do_bulding(t_taken *taken)
{
	// if (ft_strcmp(cmd[0], "exit") == 0)
	// 	return (true);
	if (ft_strcmp(taken->token, "env") == 0)
		return (true);
	else if (ft_strcmp(taken->token, "export") == 0)
		return (true);
	else if (ft_strcmp(taken->token, "unset") == 0)
		return (true);
	else if (ft_strcmp(taken->token, "echo") == 0)
		return (true);
	else if (ft_strcmp(taken->token, "pwd") == 0)
		return (true);
	else if (ft_strcmp(taken->token, "cd") == 0)
		return (true);
}
