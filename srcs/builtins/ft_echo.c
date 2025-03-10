#include "../../minishell.h"

int	ft_check_n(char	*token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
	{
		i++;
		while (token[i] == 'n')
			i++;
		if (token[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_print_echo(char **cmd, char *arg_cmd, int *i)
{
	if (!cmd[*i + 1])
		ft_printf("%s", arg_cmd);
	else
		ft_printf("%s ", arg_cmd);
}

int	ft_echo(char **cmd, t_global *global)
{
	int	i;

	i = 1;
	if (!cmd[1])
		ft_printf("\n");
	else if (ft_strcmp(cmd[1], "$?") == 0)
		ft_printf("%i\n", global->status);
	else if (ft_check_n(cmd[i]) == 1)
	{
		i++;
		while (cmd[i] && ft_check_n(cmd[i]) == 1)
			i++;
		while (cmd[i])
		{
			ft_print_echo(cmd, cmd[i], &i);
			i++;
		}
	}
	else
	{
		while (cmd[i])
		{
			ft_print_echo(cmd, cmd[i], &i);
			i++;
		}
		ft_printf("\n");
	}
	return (0);
}
