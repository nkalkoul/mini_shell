/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:47:42 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/15 15:17:26 by modavid          ###   ########.fr       */
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

char	*ft_pwd2(t_global *global)
{
	char	*pwd;
	char	*new;

	pwd = getcwd(NULL, 0);
	new = ft_strdup(pwd);	
	if (pwd == NULL)
	return (error_pwd(global), NULL);
	free(pwd);
	return (new);
}
