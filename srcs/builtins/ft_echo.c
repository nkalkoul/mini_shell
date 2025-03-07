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

void	ft_print_echo(t_taken *current)
{
	if (!current->next)
		ft_printf("%s", current->token);
	else
		ft_printf("%s ", current->token);
}

int	ft_echo(t_taken *taken)
{
	t_taken	*current;

	current = taken;
	if (!current->next)
		ft_printf("\n");
	else if (ft_check_n(current->next->token) == 1)
	{
		current = current->next;
		while (current && ft_check_n(current->token) == 1)
			current = current->next;
		while (current)
		{
			ft_print_echo(current);
			current = current->next;
		}
	}
	else
	{
		current = current->next;
		while (current)
		{
			ft_print_echo(current);
			current = current->next;
		}
		ft_printf("\n");
	}
	return (0);
}
