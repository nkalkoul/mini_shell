/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printlist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 06:26:48 by nas91             #+#    #+#             */
/*   Updated: 2025/02/13 23:51:22 by modavid          ###   ########.fr       */
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
	while (current != NULL)
	{
		i = 0;
		while (current->arg_cmd && current->arg_cmd[i])
		{
			if (current->arg_cmd)
				ft_printf("%s ", current->arg_cmd[i]);
			i++;
		}
		if (current->type)
			ft_printf("operator is %d\n", current->type);
		else
			ft_printf("\n");
		if (current->next)
		{
			printf(" |\n");
			printf(" V\n");
		}
		current = current->next;
	}
}

void	ft_printaken(t_taken *taken)
{
	t_taken	*current;

	current = taken;
	while (current != NULL)
	{
		ft_printf("\ntoken ==== %s$\n", current->token);
		current = current->next;
	}
}

int	check_equal(char *key)
{
	int	i;

	i = 0;
	while(key[i])
	{
		if (key[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_printenv(t_env *my_env)
{
	t_env	*current;
	int		i;

	i = 0;
	current = my_env;
	while (current)
	{
		if (current->value)
		{
			ft_printf("%s=", current->key);
			ft_printf("%s\n", current->value);
		}
		current = current->next;
	}
}
