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
	new->next = NULL;
	temp = *garbage;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	ft_inthebag(t_garbage *garbage, void *ptr)
{
	t_garbage	*current;

	current = garbage;
	while (current)
	{
		if (current->ptr == ptr)
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_killnode(t_garbage **garbage, void *ptr)
{
	t_garbage	*current;
	t_garbage	*temp;

	if (!garbage)
		return ;
	if (!ft_inthebag(*garbage, ptr))
	{
		free(ptr);
		return ;
	}
	current = *garbage;
	while (current->ptr != ptr)
	{
		temp = current;
		current = current->next;
	}
	if ((*garbage)->ptr == ptr)
		(*garbage) = (*garbage)->next;
	else
	{
		if (current->next)
			temp->next = current->next;
	}
	(free(ptr), free(current));
}

void	ft_finishbag(t_garbage *garbage)
{
	t_garbage	*current;

	if (!garbage)
		return ;
	current = garbage;
	while (garbage)
	{
		garbage = garbage->next;
		free(current->ptr);
		free(current);
		current = garbage;
	}
}
