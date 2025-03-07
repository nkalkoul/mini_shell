#include "../../minishell.h"

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
	if (!current->next || ft_strcmp(current->token, "export") != 0)
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

int	ft_print_export(t_taken *taken, t_global *global)
{
	t_env	*env;
	t_taken	*current;

	env = global->my_env;
	current = taken;
	if (!current->next)
	{
		while (env)
		{
			ft_printf("%s", env->key);
			if (env->value)
				ft_printf("=\"%s\"", env->value);
			ft_printf("\n");
			env = env->next;
		}
	}
	else
	{
		if (ft_export_node(taken, global) == 1)
			return (ft_putendl_fd("Error Malloc", 2), 1);
	}
	return (0);
}
