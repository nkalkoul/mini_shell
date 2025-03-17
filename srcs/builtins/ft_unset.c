/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:06:10 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 15:29:42 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_replace_node(t_env *tmp, t_env *prev, t_global *global)
{
	t_env	*save;

	save = tmp->next;
	ft_free(tmp->key);
	if (tmp->value)
		ft_free(tmp->value);
	ft_free(tmp);
	if (prev)
		prev->next = save;
	else
		global->my_env = save;
}

void	ft_free_node(char *cmd, t_global *global)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = global->my_env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(cmd, tmp->key) == 0)
		{
			ft_replace_node(tmp, prev, global);
			return ;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

int	ft_unset(char **cmd, t_global *global)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		ft_free_node(cmd[i], global);
		i++;
	}
	return (0);
}
