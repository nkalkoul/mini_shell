#include "../../minishell.h"

void	ft_free_lst(t_taken **taken)
{
	t_taken	*tmp;

	while ((*taken) != NULL)
	{
		tmp = (*taken)->next;
		free((*taken)->token);
		free(*taken);
		*taken = tmp;
	}
	free(taken);
}
