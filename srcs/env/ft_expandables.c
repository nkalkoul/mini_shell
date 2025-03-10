#include "../../minishell.h"

void	skip_current(t_taken *previous, t_taken **taken)
{
	t_taken	*tmp;

	if (previous == NULL)
		*taken = (*taken)->next;
	else
	{
		tmp = previous->next;
		previous->next = previous->next->next;
	}
}

int	ft_expand_simple(char *token, char quote, int i)
{
	i++;
	while (token[i] && token[i] != quote)
		i++;
	return (i + 1);
}

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

char	*add_environment_variable(char *token, int *i, char *result, t_global *global)
{
	char	*key;
	char	*value;

	key = get_dollar_key(token, i);
	if (key == NULL)
		return (NULL);
	value = ft_getenv(key, global);
	ft_free(key);
	if (value != NULL)
	{
		result = ft_re_strjoin(result, value);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*add_double_quotes(char *token, int *i, char *result, t_global *global)
{
	*i += 1;
	while (token[*i] && token[*i] != '\"')
	{
		if (token[*i] == '$')
			result = add_environment_variable(token, i, result, global);
		else
			result = add_other_chars(token, i, result, "$\"");
		if (result == NULL)
			return (NULL);
	}
	*i += 1;
	return (result);
}

int	ft_expand_token(t_taken	*current, t_global *global)
{
	int		i;
	char	*token;
	char	*result;

	// if (ft_delete_double_quotes(current) == 1)
	// 	return (1);
	i = 0;
	result = ft_strdup("");
	if (result == NULL)
		return (EXIT_FAILURE);
	token = current->token;
	while (token[i])
	{
		if (token[i] == '\'')
			result = add_simple_quotes(token, &i, result);
		else if (token[i] == '$')
			result = add_environment_variable(token, &i, result, global);
		else if (token[i] == '"')
			result = add_double_quotes(token, &i, result, global);
		else
			result = add_other_chars(token, &i, result, "$\"\'");
		if (result == NULL)
			return (EXIT_FAILURE);
	}
	current->token = result;
	return (0);
}

int	ft_expandables(t_taken **taken, t_global *global)
{
	t_taken	*current;
	t_taken	*previous;
	t_taken	*tmp;

	previous = NULL;
	tmp = NULL;
	current = *taken;
	while (current != NULL)
	{
		if (ft_expand_token(current, global) == 1)
			return (1);
		if (current->token[0] == '\0')
		{
			skip_current(previous, taken);
			tmp = current;
			current = current->next;
			ft_free(tmp);
		}
		else
		{
			previous = current;
			current = current->next;
		}
	}
	return (0);
}
