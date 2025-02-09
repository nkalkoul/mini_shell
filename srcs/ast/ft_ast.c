#include "../../minishell.h"

// int	ft_priority(t_cmd *current)
// {
// 	if (current->type == PIPE)
// 		return (0);
// 	if (current->type == OR || current->type == AND)
// 		return (1);
// 	return (-1);
// }
void	ft_priority(t_cmd *current)
{
	if (current->type == PIPE)
	{
		
	}
}

void	ft_ast(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->type == AND || current->type == OR)
		{
			
		}
		if (current->type == PIPE)
		{
			
		}
		else
			current = current->next
	}
}