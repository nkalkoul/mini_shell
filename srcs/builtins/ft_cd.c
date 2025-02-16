#include "../../minishell.h"

int	ft_cd(t_taken *taken)
{
	t_taken	*current;

	current = taken->next;
	if (current->next)
		return (ft_printf("Too many arguments\n"), 1);
	if (chdir(current->token) == -1)
		return (ft_printf("%s: Not a directory\n", current->token), 1);
	return (0);
}
