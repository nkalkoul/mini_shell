#include "../../minishell.h"

int	ft_lstbackadd_garbage(void *ptr, t_garbage **garbage)
{
	t_garbage	*temp;
	t_garbage	*new;

	if ((*garbage)->ptr == NULL)
	{
		(*garbage)->ptr = ptr;
		return (0);
	}
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (-1);
	new->ptr = ptr;
	temp = *garbage;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->next = NULL;
	return (0);
}
