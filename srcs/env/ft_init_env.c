#include "../../minishell.h"

int	ft_count_key(char *env)
{
	int	j;

	j = 0;
	while (env[j] != '=')
		j++;
	return (j);
}

int	ft_count_value(char *env, int j)
{
	while (env[j] != '\0')
		j++;
	return (j - 1);
}

int	ft_init_env(char *env, t_env **my_env)
{
	t_env	*new;
	int		j;
	int		start;

	j = -1;
	start = 0;
	new = ft_malloc(sizeof(t_env));
	if (!new)
		return (ft_free(*my_env), 1);
	ft_locks(new, NULL);
	new->key = ft_malloc(sizeof(char) * (ft_count_key(env) + 1));
	if (!new->key)
		return (ft_free(new), ft_free(*my_env), 1);
	ft_locks(new->key, NULL);
	while (env[++j] != '=')
		new->key[j] = env[j];
	new->key[j] = '\0';
	new->value = ft_malloc(sizeof(char) * ft_count_value(env, j));
	if (!new->value)
		return (ft_free(new), ft_free(*my_env), 1);
	ft_locks(new->value, NULL);
	while (env[++j] != '\0')
		new->value[start++] = env[j];
	new->value[start] = '\0';
	new->next = NULL;
	ft_lstbackadd_env(my_env, new);
	return (0);
}

t_env	*ft_take_myenv(char **env)
{
	int		i;
	t_env	*my_env;

	i = 0;
	my_env = NULL;
	while (env[i])
	{
		if (ft_init_env(env[i], &my_env) == 1)
			return (NULL);
		i++;
	}
	return (my_env);
}

char	*ft_getenv(char *key, t_global *global)
{
	t_env	*env;

	env = global->my_env;
	while (env)
	{
		if (env->key != NULL && ft_strcmp(key, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}
