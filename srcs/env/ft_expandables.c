#include "../../minishell.h"

// char	*ft_if_double(t_taken *current, int *i, char *result)
// {
// 	char	*tmp;
// 	int		j;

// 	j = 0;
// 	(*i)++;
// 	while(current->token[*i + j] && current->token[*i + j] != '"')
// 		j++;
// 	tmp = ft_substr(current->token, *i, j - 1);
// 	if (!tmp)
// 		return (NULL);
// 	result = ft_re_strjoin(result, tmp);
// 	if (!result)
// 		return (NULL);
// 	*i += j;
// 	return (result);
// }

// char	*ft_if_notdouble(t_taken *current, int *i, char *result)
// {
// 	int		j;
// 	char	*tmp;

// 	j = 0;
// 	while (current->token[*i +j] && current->token[*i + j] != '"')
// 		j++;
// 	tmp = ft_substr(current->token, *i, j);
// 	if (!tmp)
// 		return (NULL);
// 	result = ft_re_strjoin(result, tmp);
// 	if (!result)
// 		return (NULL);
// 	*i += j;
// 	return (result);
// }

// int	ft_delete_double_quotes(t_taken *taken)
// {
// 	t_taken	*current;
// 	char	*result;
// 	int		i;

// 	current = taken;
// 	result = ft_strdup("");
// 	if (!result)
// 		return (1);
// 	i = 0;
// 	while (current)
// 	{
// 		while (current->token[i])
// 		{
// 			if (current->token[i] == '"')
// 				result = ft_if_double(current, &i, result);
// 			else
// 				result = ft_if_notdouble(current, &i, result);
// 			if (result == NULL)
// 				return (1);
// 		}
// 		current->token = result;
// 		current = current->next;
// 	}
// 	return (0);
// }

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
	quotes = ft_substr(token, *i, quotes_size);
	if (quotes == NULL)
		return (NULL);
	*i += quotes_size;
	result = ft_re_strjoin(result, quotes);
	if (!result)
		return (NULL);
	return (result);
}

char	*add_other_chars(char *token, int *i, char *result)
{
	int		j;
	char	*temp;

	j = 0;
	while (token[*i + j] != '\0' && token[*i + j] != '$'
		&& token[*i + j] != '\'')
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
	free(key);
	if (value != NULL)
	{
		result = ft_re_strjoin(result, value);
		if (!result)
			return (NULL);
	}
	return (result);
}

char	*check_quote(char *token, int *i, char quote)
{
	char	*new;
	int		j;

	++(*i);
	j = 0;
	while (token[*i + j] != quote)
		j++;
	new = malloc(sizeof(char) * j);
	if (!new)
		return (NULL);
	j = 0;
	while (token[*i] != quote)
	{
		new[j] = token[*i];
		j++;
		(*i)++;
	}
	new[j] = '\0';
}

char	*add_double_quotes(char *token, int *i, char *result, t_global *global)
{
	char	*tmp;

	tmp = check_quote(token, i, token[*i]);
	if (!tmp)
		return (NULL);
	while (token[*i + j] != '"')
	{
		if (token[*i + j] == '$')
			result = add_environment_variable(token, &i, result, global);
	}
}

char	*delete_quote(char *current)
{
	char	*result;
	int		i;

	i = 0;
	while (current[i])
	{
		if (current[i] == '"' || current[i] == "\'")
		{
			result = ft_substr(current)
		}
	}
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
			result = add_double_quote();
		else
			result = add_other_chars(token, &i, result);
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

// int	ft_count_dollar(char *dollar, int i)
// {
// 	int	count;

// 	count = 0;
// 	while (dollar[i] != '"' && dollar[i] != '\'' && dollar[i] != '\0')
// 	{
// 		count++;
// 		i++;
// 		if (dollar[i] == '$')
// 			return (count);
// 	}
// 	return (count);
// }

// char	*ft_strdup_dollar2(char	*dollar, int i)
// {
// 	char	*key;
// 	int		j;

// 	key = ft_malloc(sizeof(char) * ft_count_dollar(dollar, i));
// 	if (!key)
// 		return (NULL);
// 	j = 0;
// 	i++;
// 	while (ft_isalnum(dollar[i]) == 1)
// 		key[j++] = dollar[i++];
// 	key[j] = '\0';
// 	return (key);
// }

// char	*ft_key_to_value(char *token, char *value)
// {
// 	char	*new;
// 	int		i;
// 	int		count;
// 	int		index;
// 	char	*tmp;

// 	i = 0;r
// 	count = 0;
// 	while (token[i] != '$')
// 	{
// 		if (token[i] == '\'')
// 			i = ft_expand_simple(token, '\'', i);
// 		else
// 			i++;
// 	}
// 	new = ft_malloc(sizeof(char) * (i + 1));
// 	if (!new)
// 		return (NULL);		// free
// 	i = 0;
// 	while (token[i] != '$')
// 	{
// 		if (token[i] == '\'')
// 		{
// 			new[i] = token[i];
// 			++i;
// 			while (token[i] != '\'')
// 			{
// 				new[i] = token[i];
// 				++i;
// 			}
// 			new[i] = token[i];
// 			++i;
// 		}
// 		else
// 		{
// 			new[i] = token[i];
// 			++i;
// 		}
// 	}
// 	new[i] = '\0';
// 	new = ft_strjoin(new, value);
// 	if (!new)
// 		return (NULL);
// 	++i;
// 	while (ft_isalnum(token[i]) == 1)
// 		++i;

// 	index = i;
// 	while (token[i] != '\0')
// 	{
// 		++i;
// 		count++;
// 	}	
// 	tmp = ft_malloc(sizeof(char) * (count + 1));
// 	if (!tmp)
// 		return (NULL);
// 	count = 0;
// 	while (token[index] != '\0')
// 		tmp[count++] = token[index++];
// 	tmp[count] = '\0';
// 	new = ft_re_strjoin(new, tmp);
// 	if (!new)
// 		return (NULL);
// 	return (new);
// }

// int	ft_expandollar(t_taken *current, t_global *global, int i)
// {
// 	char	*dollar;
// 	t_env	*tmp;

// 	dollar = ft_strdup_dollar2(current->token, i);
// 	if (!dollar)
// 		return (1);
// 	tmp = global->my_env;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(dollar, tmp->key) == 0)
// 		{
// 			current->token = ft_key_to_value(current->token,
// 				tmp->value);int	ft_expand_simple(char *token, char quote, int i)
// {
// 	i++;
// 	while (token[i] && token[i] != quote)
// 		i++;
// 	return (i + 1);
// }

// 			if (current->token == NULL)
// 				return -1;
// 			return ft_strlen(tmp->value);
// 		}
// 		tmp = tmp->next;
// 	}
// 	current->token = ft_key_to_value(current->token, "");
// 	if (current->token == NULL)
// 		return -1;
// 	return 0;
// }

// int	ft_expand_double(t_taken *current, char quote, int i, t_global *global)
// {
// 	int		j;
// 	char	*dollar;
// 	t_env	*tmp;

// 	i++;
// 	j = 0;
// 	tmp = global->my_env;
// 	if (current->token[i] == quote)
// 		i++;
// 	while (current->token[i] && current->token[i] != quote)
// 	{
// 		if (current->token[i] == '$')
// 		{
// 			j = ft_expandollar(current, global, i);
// 			if (j == -1)
// 				return (-1);
// 			i += j;
// 		}
// 		else {
// 			++i;
// 		}
// 		// printf("MDR: %s\n", current->token);
// 	}
// 	return (i);
// }

// int	ft_expand_quote(t_taken *current, t_global *global, int i)
// {
// 	int	j;

// 	j = 0;
// 	if (current->token[i] == '\'')
// 		i = ft_expand_simple(current->token, current->token[i], i);
// 	else if (current->token[i] == '"')
// 	{
// 		j = ft_expand_double(current, current->token[i], i, global);
// 		if (j == -1)
// 			return (-1);
// 		i = j;
// 	}
// 	else
// 	{
// 		if (current->token[i] == '$')
// 		{
// 			j = ft_expandollar(current, global, i);
// 			if (j == -1)
// 				return (-1);
// 			i += j;
// 		}
// 		else { ++i; }
// 	}
// 	return (i);
// }

// int	ft_expand_token(t_taken	*current, t_global *global)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (current->token[i])
// 	{
// 		j = ft_expand_quote(current, global, i);
// 		if (j == -1)
// 			return (1);
// 		i = j;
// 	}
// 	return (0);
// }





/*
fn {
	if '&&' -> fork a gauche, attendre, etc...
	if '||' -> fork a gauche, attendre, etc...
	if '|' -> fork a gauche, attendre, etc...
	if CMD -> exec
}
*/
