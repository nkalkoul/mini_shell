/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:25 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:07:26 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_node_env(t_global *global)
{
	t_env	*env;
	int		i;

	env = global->my_env;
	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i + 1);
}

char	**ft_put_env2d(t_global *global)
{
	t_env	*env;
	char	**tab;
	int		i;

	env = global->my_env;
	i = 0;
	tab = ft_malloc(sizeof(char *) * ft_count_node_env(global));
	if (!tab)
		return (NULL);
	while (env)
	{
		tab[i] = ft_strdup("");
		tab[i] = ft_re_strjoin(tab[i], env->key);
		tab[i] = ft_re_strjoin(tab[i], "=");
		tab[i] = ft_re_strjoin(tab[i], env->value);
		if (!tab[i])
			return (NULL);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
