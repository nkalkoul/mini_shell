/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:06:36 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:06:37 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_print_export(char **cmd, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	if (!cmd[1])
	{
		while (env)
		{
			ft_printf(1, "%s", env->key);
			if (env->value)
				ft_printf(1, "=\"%s\"", env->value);
			ft_printf(1, "\n");
			env = env->next;
		}
	}
	else
		ft_export_node(cmd, global);
	return (0);
}
