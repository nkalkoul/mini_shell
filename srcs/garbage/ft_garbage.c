/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:53 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:08:02 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free(void *ptr)
{
	static int				i = -1;
	static t_garbage_head	*garbage;

	if (ptr == ((void *) -1))
	{
		i = -1;
		ft_finishbag(garbage);
		garbage = ft_malloc(-1);
		return ;
	}
	if (!ptr)
		return ;
	if (i == -1)
	{
		garbage = ptr;
		i++;
		return ;
	}
	else
		ft_killnode(garbage, ptr);
}

void	*ft_malloc(long int l)
{
	static t_garbage_head	*garbage = NULL;
	void					*ptr;

	if (l == -1)
	{
		garbage = NULL;
		return (NULL);
	}
	if (garbage == NULL)
	{
		garbage = malloc(sizeof(t_garbage_head));
		if (garbage == NULL)
			return (NULL);
		ft_memset(garbage, 0, sizeof(t_garbage_head));
		ft_free(garbage);
		ft_locks(NULL, garbage);
		ft_unlocks(NULL, garbage);
		ft_clearbag(garbage);
	}
	ptr = malloc(l);
	if (!ptr)
		return (free(garbage), NULL);
	ft_lstbackadd_garbage(ptr, garbage);
	return (ptr);
}
