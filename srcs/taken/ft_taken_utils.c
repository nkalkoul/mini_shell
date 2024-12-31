/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 06:26:48 by nas91             #+#    #+#             */
/*   Updated: 2024/12/31 18:27:57 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printcmd(t_cmd *cmd)
{
	t_cmd	*curent;
	int		i;

	curent = cmd;
	while (curent != NULL)
	{
		i = 0;
	while (curent->arg_cmd[i])
		{
			if (curent->arg_cmd)
				ft_printf("------cmd---- = %s$\n", curent->arg_cmd[i]);
			i++;
		}
		printf("ensuite\n");
		curent = curent->next;
	}
}

void	ft_printaken(t_taken *taken)
{
	t_taken	*curent;

	curent = taken;
	while (curent != NULL)
	{
		ft_printf(" chaine = == %s$\n", curent->token);
		curent = curent->next;
	}
}

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
