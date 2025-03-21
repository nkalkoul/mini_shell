/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expandables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:14 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 20:52:12 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_dollar_key(char *token, int *i)
{
	int		j;
	char	*key;

	++(*i);
	j = 0;
	if (token[*i] == '?')
		j++;
	else
		while (ft_isalnum(token[*i + j]) == 1 || token[*i + j] == '_')
			++j;
	if (j == 0)
	{
		key = ft_strdup("$");
		if (!key)
			return (NULL);
	}
	else
	{
		key = ft_substr(token, *i, j);
		if (!key)
			return (NULL);
	}
	*i += j;
	return (key);
}

char	*add_other_chars(char *token, int *i, char *result, char *set)
{
	int		j;
	char	*temp;

	j = 0;
	while (token[*i + j] != '\0' && ft_strchr(set, token[*i + j]) == NULL)
		++j;
	temp = ft_substr(token, *i, j);
	if (temp == NULL)
		return (NULL);
	*i += j;
	result = ft_re_strjoin(result, temp);
	if (!result)
		return (NULL);
	return (result);
}

char	*add_env_variable(char *token, int *i, char *result, t_global *global)
{
	char	*key;
	char	*value;

	key = get_dollar_key(token, i);
	if (key == NULL)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
		value = ft_itoa(global->status);
	else
		value = ft_getenv(key, global);
	ft_free(key);
	if (value != NULL)
		result = ft_re_strjoin(result, value);
	return (result);
}

char	*ft_expand_token(char *arg, t_global *global)
{
	int		i;
	char	*token;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	token = arg;
	while (token[i])
	{
		if (token[i] == '\'')
			result = add_simple_quotes(token, &i, result);
		else if (token[i] == '$')
			result = add_env_variable(token, &i, result, global);
		else if (token[i] == '"')
			result = add_double_quotes(token, &i, result, global);
		else
			result = add_other_chars(token, &i, result, "$\"\'");
		if (result == NULL)
			return (NULL);
	}
	return (result);
}

int	ft_expandables(t_cmd *cmd, t_global *global)
{
	int		i;
	t_cmd	*current;
	t_files	*files;

	current = cmd;
	i = 0;
	while (current && current->arg_cmd && current->arg_cmd[i])
	{
		current->arg_cmd[i] = ft_expand_token(current->arg_cmd[i], global);
		i++;
	}
	files = current->files;
	while (files)
	{
		files->path = ft_expand_token(files->path, global);
		files = files->next;
	}
	return (0);
}
