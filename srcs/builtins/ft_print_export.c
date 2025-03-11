#include "../../minishell.h"

int	ft_print_export(char **cmd, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	if (!cmd[1])
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
		ft_export_node(cmd, global);
	return (0);
}
