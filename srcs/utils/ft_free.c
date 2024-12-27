#include "../../minishell.h"

void	ft_free_lst(t_taken **taken)
{
	t_taken	*tmp;
	t_taken	*next;

	tmp = *taken;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = next;
	}
}
