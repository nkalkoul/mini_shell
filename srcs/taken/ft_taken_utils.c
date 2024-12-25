/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 06:26:48 by nas91             #+#    #+#             */
/*   Updated: 2024/12/26 00:50:13 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_printcmd(t_cmd *cmd)
// {
// 	t_cmd	*curent;
// 	int		i;

// 	i = 0;
// 	curent = cmd;
// 	while (curent != NULL)
// 	{
// 		ft_printf(" <-----cmd-----> %s$\n", curent->redir);
// 		curent = curent->next;
// 	}
// }

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
