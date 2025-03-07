#include "../../minishell.h"

int	ft_cd(t_taken *taken, t_global *global)
{
	t_taken	*current;

	current = taken->next;
	global->status = 0;
	if (current->next)
	{
		ft_printf("Too many arguments\n");
		global->status = 1;
	}
	if (chdir(current->token) == -1)
	{
		ft_printf("%s: Not a directory\n", current->token);
		global->status = 1;
	}
	return (global->status);
}
