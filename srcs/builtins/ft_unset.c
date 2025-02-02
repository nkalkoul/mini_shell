#include "../../minishell.h"

void	ft_free_node(t_taken *current, t_env *my_env)
{
	t_env	*save;
	t_env	*tmp;
	t_env	*prev;

	tmp = my_env;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(current->token, tmp->key) == 0)
		{
			save = tmp->next;
			free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = save;
			if (prev)
				prev->next = tmp;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
}

void	ft_unset(t_taken *taken, t_global *global)
{
	t_taken	*current;

	current = taken->next;
	while (current)
	{
		ft_free_node(current, global->my_env);
		current = current->next;
	}
}
