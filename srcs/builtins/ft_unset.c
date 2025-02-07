#include "../../minishell.h"

void	ft_free_node(t_taken *current, t_global *global)
{
	t_env	*save;
	t_env	*tmp;
	t_env	*prev;

	tmp = global->my_env;
	prev = NULL;
	while (tmp)
	{
		printf("current: %s\n", tmp->key);
		printf("next: %s\n", tmp->next->key);
		if (ft_strcmp(current->token, tmp->key) == 0)
		{
			save = tmp->next;
			ft_free(tmp->key);
			if (tmp->value)
				ft_free(tmp->value);
			ft_free(tmp);
			if (prev)
				prev->next = save;
			else
				global->my_env = save;
			return ;
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
		ft_free_node(current, global);
		current = current->next;
	}
}
