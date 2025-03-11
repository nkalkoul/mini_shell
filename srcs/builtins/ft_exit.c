#include "../../minishell.h"

unsigned long	ft_atol(const char *s1)
{
	int				i;
	unsigned long	nbr;
	int				sign;

	sign = 1;
	i = 0;
	nbr = 0;
	while (((s1[i] >= 9 && s1[i] <= 13) || s1[i] == 32) && s1[i])
		i++;
	if (s1[i] == '-' || s1[i] == '+')
	{
		if (s1[i] == '-')
			sign = -1;
		i++;
	}
	while (s1[i] && ft_isdigit(s1[i]) == 1)
	{
		nbr = 10 * nbr + (s1[i] - 48);
		i++;
	}
	return (nbr * sign);
}

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
	else if (ft_atol(cmd[1]) > 9223372036854775807
		|| ft_is_arg_num(cmd[1]) == 0)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putendl_fd(" numeric argument required", 2);
		ft_free_and_exit(2);
	}
	else if (ft_atol(cmd[1]) <= 9223372036854775807 && cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	else if (cmd[1])
		ft_free_and_exit(atoi(cmd[1]));
	else
		ft_free_and_exit(0);
	return (0);
}
