#include "../../minishell.h"

void	ft_echo(t_taken *taken)
{
	t_taken	*current;

	if (ft_strncmp(current->token, "echo", 4) == 0)
	{
		if (!current->next)
			ft_printf("\n");
	}
}