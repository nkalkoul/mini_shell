/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:06:41 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 20:17:44 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	set_oldpwd(t_global *global, char *pwd)
{
	t_env	*env;

	env = global->my_env;
	while (env)
	{
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			ft_free(env->value);
			env->value = ft_strdup(pwd);
			free(pwd);
			ft_locks(env->value, NULL);
			return ;
		}
		env = env->next;
	}
	free(pwd);
}

void	set_pwd(t_global *global)
{
	t_env	*env;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	env = global->my_env;
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			ft_free(env->value);
			env->value = ft_strdup(pwd);
			free(pwd);
			ft_locks(env->value, NULL);
			return ;
		}
		env = env->next;
	}
	free(pwd);
}

int	ft_cd(char **cmd, t_global *global)
{
	char	*pwd;

	global->status = 0;
	if (cmd[2])
	{
		ft_printf(2, "Too many arguments\n");
		global->status = 1;
	}
	pwd = getcwd(NULL, 0);
	if (chdir(cmd[1]) == -1)
	{
		ft_printf(2, "%s: Not a directory\n", cmd[1]);
		global->status = 1;
	}
	set_pwd(global);
	set_oldpwd(global, pwd);
	return (global->status);
}
