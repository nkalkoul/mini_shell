#include "../../minishell.h"

int	ft_priority(t_cmd *current)
{
	if (current->type == PIPE)
		return (0);
	if (current->type == OR || current->type == AND)
		return (1);
	return (-1);
}

