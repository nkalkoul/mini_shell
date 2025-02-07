#include "../../minishell.h"

int	ft_lstbackadd_garbage(void *ptr, t_garbage_head *garbage)
{
	t_garbage	*temp;
	t_garbage	*new;

	if (garbage->head == NULL)
	{
		garbage->head = malloc(sizeof(t_garbage));
		garbage->head->ptr = ptr;
		garbage->head->next = NULL;
		return (0);
	}
	new = malloc(sizeof(t_garbage));
	if (!new)
		return (-1);
	new->ptr = ptr;
	new->next = NULL;
	temp = garbage->head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	return (0);
}

int	ft_inthebag(t_garbage_head *garbage, void *ptr)
{
	t_garbage	*current;

	current = garbage->head;
	while (current)
	{
		if (current->ptr == ptr)
			return (1);
		current = current->next;
	}
	return (0);
}

void	ft_killnode(t_garbage_head *garbage, void *ptr)
{
	t_garbage	*current;
	t_garbage	*temp;

	if (!garbage)
		return ;
	if (!ft_inthebag(garbage, ptr))
	{
		free(ptr);
		return ;
	}
	current = garbage->head;
	while (current->ptr != ptr)
	{
		temp = current;
		current = current->next;
	}
	if (garbage->head->ptr == ptr)
		garbage->head = garbage->head->next;
	else
		temp->next = current->next;
	(free(ptr), free(current));
}

void	ft_finishbag(t_garbage_head *garbage)
{
	t_garbage	*current;

	if (!garbage->head)
		return ;
	current = garbage->head;
	while (garbage->head)
	{
		garbage->head = garbage->head->next;
		free(current->ptr);
		free(current);
		current = garbage->head;
	}
	free(garbage->head);
}
