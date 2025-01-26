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

char	*ft_export_key(char *key, t_env *new)
{
	int		i;

	new->key = malloc(sizeof(char) * (ft_count_key_export(key) + 1));
	if (!new->key)
		return (NULL);
	i = 0;
	while (key[i] && key[i] != '=')
	{
		new->key[i] = key[i];
		i++;
	}
	new->key[i] = '\0';
	return (new->key);
}

char	*ft_export_value(char *value, t_env *new)
{
	int	i;

	i = ft_count_key_export(value);
	if (value[i] == '\0')
		return (NULL);
	while (value[i] != '\0')
		i++;
	new->value = malloc(sizeof(char) * i);
	if (!new->value)
		return (NULL);
	i = ft_count_key_export(value) + 1;
	while (value[i] == '\0')
	{
		new->value[i] = value[i];
		i++;
	}
	new->value[i] = '\0';
	return (new->value);
}

int	ft_export_node(t_taken *taken, t_global *global)
{
	t_taken *current;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (1);
	current = taken;
	if (current->next && ft_strncmp(current->token, "export", 6) == 0)
		current = current->next;
	while (current)
	{
		
	}
	
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
}
