#include "../../minishell.h"

int	ft_export(t_taken *taken)
{
	t_taken	*current;

	current = taken;
	if (current->next != NULL)
		return (1);
	if (ft_strncmp(current->token, "export", 6) == 0)
		return (0);
	return (1);
}

int	ft_count_key_export(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	return (i);
}

char	*ft_export_key(char *key, t_env *new, int *i)
{
	new->key = ft_malloc(sizeof(char) * (ft_count_key_export(key) + 1));
	if (!new->key)
		return (NULL);
	while (key[*i] && key[*i] != '=')
	{
		new->key[*i] = key[*i];
		(*i)++;
	}
	new->key[*i] = '\0';
	return (new->key);
}

char	*ft_export_value(char *value, t_env *new, int *i)
{
	int	j;
	int	count;

	j = *i;
	count = 0;
	while (value[*i] != '\0')
	{
		(*i)++;
		count++;
	}
	new->value = ft_malloc(sizeof(char) * (count + 1));
	if (!new->value)
		return (NULL);
	count = 0;
	while (value[j] != '\0')
	{
		new->value[count] = value[j];
		j++;
		count++;
	}
	new->value[count] = '\0';
	return (new->value);
}

int	ft_export_node(t_taken *taken, t_global *global)
{
	t_taken *current;
	t_env	*new;
	int		i;

	current = taken;
	if (!current->next || ft_strncmp(current->token, "export", 6) != 0)
		return (1);
	current = current->next;
	while (current)
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (1);
		i = 0;
		while (current->token[i])
		{
			new->key = ft_export_key(current->token, new, &i);
			if (!new->key)
				return (1);
			if (current->token[i] == '\0')
				break ;
			i++;
			new->value = ft_export_value(current->token, new, &i);
			if (!new->value)
				return (1);
		}
		ft_lstbackadd_env(&(global->my_env), new);
		current = current->next;
	}
	return (0);
}

void	ft_print_export(t_global *global, t_taken *taken)
{
	t_env	*tmp;

	tmp = global->my_env;
	if (ft_export(taken) == 0)
	{
		while (tmp)
		{
			ft_printf("%s=", tmp->key);
			ft_printf("%s\n", tmp->value);
			tmp = tmp->next;
		}
	}
	if (ft_export_node(taken, global) == 0)
	{
		while (tmp)
		{
			// if (tmp->value)
			ft_printf("%s=%s\n", tmp->key, tmp->value);
			// else
			// 	ft_printf("%s\n", tmp->key);
			tmp = tmp->next;
		}
	}
}
