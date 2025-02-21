#include "../../minishell.h"

void	ft_exec(t_cmd *cmd, t_global *global)
{
	t_cmd *current;

	current = cmd->top;
	//if (bulltin et que ya pas d'autre current de next)
	while (current)
	{
		ft_fork();
	}
}
