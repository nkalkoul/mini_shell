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

void	ft_unset_in_export(t_global *global, char *key)
{
	t_env	*env;
	t_env	*save;
	t_env	*prev;

	prev = NULL;
	env = global->my_env;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
		{
			ft_replace_node(env, prev, global);
			break ;
		}
		else
		{
			prev = env;
			env = env->next;
		}
	}
}

void	ft_export_node(char **cmd, t_global *global)
{
	t_env	*new;
	int		i;
	int		j;

	i = 1;
	while (cmd[i])
	{
		new = ft_calloc(1, sizeof(t_env));
		j = 0;
		while (cmd[i][j])
		{
			new->key = ft_export_key(cmd[i], new, &j);
			if (cmd[i][j] == '\0')
				break ;
			j++;
			new->value = ft_export_value(cmd[i], new, &j);
		}
		ft_unset_in_export(global, new->key);
		ft_lstbackadd_env(&(global->my_env), new);
		i++;
	}
}
