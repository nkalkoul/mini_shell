#include "../../minishell.h"

void	ft_free_and_exit(int status)
{
	ft_free((void *) -1);
	exit(status);
}

int	ft_is_arg_num(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isdigit(cmd[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_exit(char **cmd, t_global *global)
{
	ft_printf("exit\n");
	if (!cmd[1])
		ft_free_and_exit(0);
	else if (ft_strlen(cmd[1]) >= 20 || ft_is_arg_num(cmd[1]) == 1)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd("numeric argument necesitary", 2);
		ft_free_and_exit(0);
	}
	else if (ft_strlen(cmd[1]) < 20 && cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		global->status = 1;
	}
}
