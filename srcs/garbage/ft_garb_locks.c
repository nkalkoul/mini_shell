/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garb_locks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:48 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:07:49 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_locks(void *ptr, t_garbage_head *garb)
{
	static t_garbage_head	*garbage = NULL;
	t_garbage				*current;

	if (garb != NULL)
	{
		garbage = garb;
		return ;
	}
	if (!ptr)
		return ;
	current = garbage->head;
	while (current != NULL && current->ptr != ptr)
		current = current->next;
	if (!current)
		return ;
	current->lock = 1;
}

void	ft_unlocks(void *ptr, t_garbage_head *garb)
{
	static t_garbage_head	*garbage = NULL;
	t_garbage				*current;

	if (garb != NULL)
	{
		garbage = garb;
		return ;
	}
	current = garbage->head;
	while (current && current->ptr != ptr)
		current = current->next;
	if (!current)
		return ;
	current->lock = 0;
}

void	ft_clearbag(t_garbage_head *garb)
{
	static t_garbage_head	*garbage = NULL;
	t_garbage				*current;
	t_garbage				*temp;

	if (!garbage)
	{
		garbage = garb;
		return ;
	}
	current = garbage->head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		if (temp->lock == 0)
			ft_killnode(garbage, temp->ptr);
	}
}
