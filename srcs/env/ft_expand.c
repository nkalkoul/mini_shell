#include "../../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup_dollar(char *dollar)
{
	int		i;
	int		j;
	char	*key;

	i = 0;
	while (dollar[i] != '\0')
		i++;
	key = malloc(sizeof(char) * i);
	if (!key)
		return (NULL);
	j = 0;
	i = 1;
	while (dollar[i] != '\0')
		key[j++] = dollar[i++];
	key[j] = '\0';
	return (key);
}

int	ft_expand_key(t_taken *taken, t_global *global)
{
	t_taken	*current;
	char	*dollar;

	current = taken;
	while (current != NULL)
	{
		if (current->token[0] == '$')
		{
			dollar = ft_strdup_dollar(current->token);
			if (!dollar)
				return (1);
			while (global->my_env)
			{
				if (ft_strcmp(global->my_env->key, dollar) == 0)
					current->token = ft_strdup(global->my_env->value);
				global->my_env = global->my_env->next;
			}
		}
		current = current->next;
	}
	return (0);
}
