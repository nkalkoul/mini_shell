/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:19 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:23:50 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_init_env(char *env, t_env **my_env)
{
	t_env	*new;
	int		j;
	int		start;

	j = -1;
	start = 0;
	new = ft_malloc(sizeof(t_env));
	ft_locks(new, NULL);
	new->key = ft_malloc(sizeof(char) * (ft_count_key(env) + 1));
	ft_locks(new->key, NULL);
	while (env[++j] != '=')
		new->key[j] = env[j];
	new->key[j] = '\0';
	new->value = ft_malloc(sizeof(char) * ft_count_value(env, j));
	ft_locks(new->value, NULL);
	while (env[++j] != '\0')
		new->value[start++] = env[j];
	new->value[start] = '\0';
	new->next = NULL;
	ft_lstbackadd_env(my_env, new);
	return (0);
}

t_env	*ft_take_env_null(t_global *g)
{
	t_env	*my_env;
	t_env	*pwd;

	pwd = ft_malloc(sizeof(t_env));
	ft_locks(pwd, NULL);
	pwd->key = ft_strdup("PWD");
	ft_locks(pwd->key, NULL);
	pwd->value = ft_pwd2();
	ft_locks(pwd->value, NULL);
	pwd->next = NULL;
	my_env = ft_malloc(sizeof(t_env));
	ft_locks(my_env, NULL);
	my_env->key = ft_strdup("SHLVL");
	ft_locks(my_env->key, NULL);
	my_env->value = ft_strdup(ft_itoa(++g->lvl));
	ft_locks(my_env->value, NULL);
	my_env->next = NULL;
	pwd->next = my_env;
	return (pwd);
}

t_env	*ft_take_myenv(char **env, t_global *g)
{
	int		i;
	t_env	*my_env;

	i = 0;
	my_env = NULL;
	if (!*env)
		return (ft_take_env_null(g));
	while (env[i])
	{
		if (ft_init_env(env[i], &my_env) == 1)
			return (NULL);
		i++;
	}
	return (my_env);
}

char	*ft_getenv(char *key, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	while (env)
	{
		if (env->key != NULL && ft_strcmp(key, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
