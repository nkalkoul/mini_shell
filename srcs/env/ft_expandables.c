#include "../../minishell.h"

// char	*ft_strdup_dollar(char *dollar)
// {
// 	int		i;
// 	int		j;
// 	char	*key;

// 	i = 0;
// 	while (dollar[i] != '\0' && dollar[i] != '\'' && dollar[i] != '"')
// 		i++;
// 	key = malloc(sizeof(char) * i);
// 	if (!key)
// 		return (NULL);
// 	j = 0;
// 	i = 1;
// 	while (dollar[i] != '\0')
// 		key[j++] = dollar[i++];
// 	key[j] = '\0';
// 	return (key);
// }

// int	ft_expand_key(t_taken *taken, t_global *global)
// {
// 	t_taken	*current;
// 	char	*dollar;

// 	current = taken;
// 	while (current != NULL)
// 	{
// 		if (current->token[0] == '$')
// 		{
// 			dollar = ft_strdup_dollar(current->token);
// 			if (!dollar)
// 				return (1);
// 			while (global->my_env)
// 			{
// 				if (ft_strcmp(global->my_env->key, dollar) == 0)
// 					current->token = ft_strdup(global->my_env->value);
// 				global->my_env = global->my_env->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_count_dollar(char *dollar, int i)
{
	int	count;

	count = 0;
	while (dollar[i] != '"' && dollar[i] != '\'' && dollar[i] != '\0')
	{
		count++;
		i++;
		if (dollar[i] == '$')
			return (count);
	}
	return (count);
}

char	*ft_strdup_dollar2(char	*dollar, int i)
{
	char	*key;
	int		j;

	key = malloc(sizeof(char) * ft_count_dollar(dollar, i));
	if (!key)
		return (NULL);
	j = 0;
	i++;
	while (dollar[i] != '"' && dollar[i] != '\''
		&& dollar[i] != '\0' && dollar[i] != '$')
		key[j++] = dollar[i++]; 
	key[j] = '\0';
	return (key);
}

char	*ft_key_to_value(char *token, char *value)
{
	char	*new;
	int		i;
	int		count;
	int		index;
	char	*tmp;

	i = 0;
	count = 0;
	while (token[i] != '$')
		i++;
	new = malloc(sizeof(char) * i);
	if (!new)
		return (NULL);		// free
	i = -1;
	while (token[++i] != '$')
		new[i] = token[i];
	new[i] = '\0';
	new = ft_strjoin(new, value);
	if (!new)
		return (NULL);
	while (token[i] != '\'' && token[i] != '"' && token[i] != '\0')
	{
		i++;
		if (token[i] == '$')
			break;
	}
	index = i;
	while (token[++i] != '\0')
		count++;
	tmp = malloc(sizeof(char) * count + 1);
	if (!tmp)
		return (NULL);
	count = 0;
	while (token[index] != '\0')
		tmp[count++] = token[index++];
	tmp[count] = '\0';
	new = ft_re_strjoin(new, tmp);
	if (!new)
		return (NULL);
	return (new);
}

int	ft_expandollar(t_taken *current, t_global *global, int i)
{
	char	*dollar;
	t_env	*tmp;

	dollar = ft_strdup_dollar2(current->token, i);
	if (!dollar)
		return (1);
	tmp = global->my_env;
	while (tmp)
	{
		if (ft_strcmp(dollar, tmp->key) == 0)
		{
			current->token = ft_key_to_value(current->token,
				tmp->value);
			if (!current->token)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	ft_expand_double(t_taken *current, char quote, int i, t_global *global)
{
	char	*dollar;
	t_env	*tmp;

	i++;
	tmp = global->my_env;
	if (current->token[i] == quote)
		i++;
	while (current->token[i] && current->token[i] != quote)
	{
		if (current->token[i] == '$')
		{
			if (ft_expandollar(current, global, i) == 1)
				return (-1);
		}
		i++;
	}
	return (i);
}

int	ft_expand_simple(char *token, char quote, int i)
{
	i++;
	while (token[i] && token[i] != quote)
		i++;
	return (i + 1);
}

int	ft_expand_quote(t_taken *current, t_global *global, int i)
{
	int	j;

	j = 0;
	if (current->token[i] == '\'')
		i += ft_expand_simple(current->token, current->token[i], i);
	else if (current->token[i] == '"')
	{
		j = ft_expand_double(current, current->token[i], i, global);
		if (j == -1)
			return (-1);
		i += j;
	}
	else
	{
		if (current->token[i] == '$')
		{
			if (ft_expandollar(current, global, i) == 1)
				return (-1);
		}
		i++;
	}
	return (i);
}

int	ft_expand_token(t_taken	*current, t_global *global)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (current->token[i])
	{
		j = ft_expand_quote(current, global, i);
		if (j == -1)
			return (1);
		i += j;
	}
	return (0);
}

int	ft_expandables(t_taken *taken, t_global *global)
{
	t_taken	*current;

	current = taken;
	while (current != NULL)
	{
		if (ft_expand_token(current, global) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
