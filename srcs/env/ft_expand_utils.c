/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:08 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:07:09 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes_len(char *token, int i, char quote)
{
	int	j;

	j = 1;
	while (token[i + j] && token[i + j] != quote)
		++j;
	return (j + 1);
}

char	*add_simple_quotes(char *token, int *i, char *result)
{
	int		quotes_start;
	int		quotes_size;
	char	*quotes;

	quotes_size = quotes_len(token, *i, '\'');
	quotes = ft_substr(token, *i + 1, quotes_size - 2);
	if (quotes == NULL)
		return (NULL);
	*i += quotes_size;
	result = ft_re_strjoin(result, quotes);
	if (!result)
		return (NULL);
	return (result);
}

char	*add_double_quotes(char *token, int *i, char *result, t_global *global)
{
	*i += 1;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
			result = add_env_variable(token, i, result, global);
		else
			result = add_other_chars(token, i, result, "$\"");
		if (result == NULL)
			return (NULL);
	}
	*i += 1;
	return (result);
}

void	ft_shlvlup(t_global *g)
{
	t_env	*current;

	current = g->my_env;
	while (current)
	{
		if (ft_strcmp("SHLVL", current->key) == 0)
		{
			g->lvl = ft_atoi(current->value) + 1;
			current->value = ft_itoa(g->lvl);
		}
		current = current->next;
	}
}
