/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:47:42 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/11 12:03:23 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_pwd(t_global *global)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd("pwd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	}
	perror("");
	global->status = 1;
}

int	ft_pwd(t_global *global)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (error_pwd(global), 1);
	ft_printf(1, "%s\n", pwd);
	free(pwd);
	return (0);
}
