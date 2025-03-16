/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:06:26 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:06:27 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_n(char	*token)
{
	int	i;

	i = 0;
	if (token[i] == '-')
	{
		i++;
		while (token[i] == 'n')
			i++;
		if (token[i] == '\0')
			return (1);
	}
	return (0);
}

void	ft_print_echo(char **cmd, int *i)
{
	while (cmd[*i])
	{
		if (!cmd[*i + 1])
			ft_printf(1, "%s", cmd[*i]);
		else
			ft_printf(1, "%s ", cmd[*i]);
		(*i)++;
	}
}

int	ft_echo(char **cmd, t_global *global)
{
	int	i;

	i = 1;
	if (!cmd[1])
		ft_putstr_fd("\n", 1);
	else if (ft_strcmp(cmd[1], "$?") == 0)
		ft_printf(1, "%i\n", global->status);
	else if (ft_check_n(cmd[i]) == 1)
	{
		i++;
		while (cmd[i] && ft_check_n(cmd[i]) == 1)
			i++;
		ft_print_echo(cmd, &i);
	}
	else
	{
		ft_print_echo(cmd, &i);
		ft_printf(1, "\n");
	}
	return (0);
}
