#include "../../minishell.h"

void	ft_recursive_exec(t_cmd *top)
{
	if (top == NULL)
		return ;
	if (top->type == WORD)
	{
		ft_execve();
		return ;
	}
	else
	{
		
	}
}

void	ft_exec(t_cmd *cmd, t_global *global)
{
	t_cmd *current;

	current = ft_ast(cmd);

}
