/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taken_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 06:26:48 by nas91             #+#    #+#             */
/*   Updated: 2025/01/04 00:08:36 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printfiles(t_cmd *cmd)
{
	t_files	*current;
	int		i;

	i = 0;
	current = cmd->files;
	while (current)
	{
		printf("redir[%d] = '%s %s'\n", i, current->redir, current->path);
		i++;
		current = current->next;
	}
}

void	ft_printcmd(t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	current = cmd;
	printf("\n");
	while (current != NULL)
	{
		i = 0;
		while (current->arg_cmd && current->arg_cmd[i])
		{
			if (current->arg_cmd)
				ft_printf("%s ", current->arg_cmd[i]);
			i++;
		}
		ft_printf("\n");
		if (current->next)
		{
			printf("|\n");
			printf("V\n");
		}
		current = current->next;
	}
	printf("\n");
}

void	ft_printenv(t_env *my_env)
{
	t_env	*current;
	int		i;

	i = 0;
	current = my_env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

// void	ft_printaken(t_taken *taken)
// {
// 	t_taken	*current;

// 	current = taken;
// 	while (current != NULL)
// 	{
// 		// ft_printf(" chaine = == %s$\n", current->token);
// 		current = current->next;
// 	}
// }

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
