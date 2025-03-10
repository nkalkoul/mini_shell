#include "../../minishell.h"

void	ft_free2d(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_free(str[i]);
		i++;
	}
	ft_free(str);
}

void	ft_free_lst(t_taken **taken)
{
	t_taken	*tmp;
	t_taken	*next;

	tmp = *taken;
	while (tmp != NULL)
	{
		next = tmp->next;
		ft_free(tmp->token);
		ft_free(tmp);
		tmp = next;
	}
}

void	ft_free_files(t_files **files)
{
	t_files	*tmp;
	t_files	*next;

	tmp = *files;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->path != NULL)
			ft_free(tmp->path);
		ft_free(tmp);
		tmp = next;
	}
}

void	ft_free_cmd(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_cmd	*next;

	tmp = cmd;
	while (tmp != NULL)
	{
		next = tmp->next;
		if (tmp->arg_cmd != NULL)
			ft_free(tmp->arg_cmd);
		ft_free(tmp);
		tmp = next;
	}
}

void	ft_free_env(t_env *my_env)
{
	t_env	*tmp;
	t_env	*next;

	tmp = my_env;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			ft_free(tmp->key);
		if (tmp->value)
			ft_free(tmp->value);
		ft_free(tmp);
		tmp = next;
	}
}
