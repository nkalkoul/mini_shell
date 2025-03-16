/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbackadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:09:35 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:09:36 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstbackadd(t_taken **lst, t_taken *new)
{
	t_taken	*temp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}

void	ft_lstbackadd_files(t_files **lst, t_files *new)
{
	t_files	*temp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}

void	ft_lstbackadd_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*temp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}

void	ft_lstbackadd_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}
