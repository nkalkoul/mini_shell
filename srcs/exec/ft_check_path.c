#include "../../minishell.h"

char	*ft_split_value(char *cmd, char *value)
{
	char	**tab;
	int		i;

	tab = ft_split(value, ':');
	if (!tab)
		return (NULL);
	i = -1;
	while (tab[++i])
	{
		tab[i] = ft_re_strjoin(tab[i], "/");
		tab[i] = ft_re_strjoin(tab[i], cmd);
		if (access(tab[i], X_OK) == 0)
			break ;
	}
	if (tab[i] == NULL)
		return (NULL);
	return (ft_strdup(tab[i]));
}

char	*ft_pathfinder(t_cmd *cmd, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	if (!env)
		return (NULL);
	if (!cmd->arg_cmd)
		exit(1);
	if (access(cmd->arg_cmd[0], X_OK) == 0)
		return (ft_strdup(cmd->arg_cmd[0]));
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			break ;
		env = env->next;
		if (!env)
			return (NULL);
	}
	return (ft_split_value(cmd->arg_cmd[0], env->value));
}
