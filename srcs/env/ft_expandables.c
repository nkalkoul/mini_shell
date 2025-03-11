#include "../../minishell.h"

char	*get_dollar_key(char *token, int *i)
{
	int		j;
	char	*key;

	++(*i);
	j = 0;
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

	current = cmd;
	// while (current)
	// {
		i = 0;
		while (current && current->arg_cmd[i])
		{
			if (ft_strcmp(current->arg_cmd[i], "$?") == 0)
				i++;
			else
			{
				current->arg_cmd[i] = ft_expand_token(current->arg_cmd[i], global);
				i++;
			}
		}
	// 	// current = current->next;
	// }
	return (0);
}

// int	ft_expand_token(t_taken	*current, t_global *global)
// {
// 	int		i;
// 	char	*token;
// 	char	*result;

// 	i = 0;
// 	result = ft_strdup("");
// 	if (result == NULL)
// 		return (EXIT_FAILURE);
// 	token = current->token;
// 	while (token[i])
// 	{
// 		if (token[i] == '\'')
// 			result = add_simple_quotes(token, &i, result);
// 		else if (token[i] == '$')
// 			result = add_environment_variable(token, &i, result, global);
// 		else if (token[i] == '"')
// 			result = add_double_quotes(token, &i, result, global);
// 		else
// 			result = add_other_chars(token, &i, result, "$\"\'");
// 		if (result == NULL)
// 			return (EXIT_FAILURE);
// 	}
// 	current->token = result;
// 	return (0);
// }

// int	ft_expandables(t_taken **taken, t_global *global)
// {
// 	t_taken	*current;
// 	t_taken	*previous;
// 	t_taken	*tmp;

// 	previous = NULL;
// 	tmp = NULL;
// 	current = *taken;
// 	while (current != NULL)
// 	{
// 		if (ft_expand_token(current, global) == 1)
// 			return (1);
// 		if (current->token[0] == '\0')
// 		{
// 			skip_current(previous, taken);
// 			tmp = current;
// 			current = current->next;
// 			ft_free(tmp);
// 		}
// 		else
// 		{
// 			previous = current;
// 			current = current->next;
// 		}
// 	}
// 	return (0);
// }
