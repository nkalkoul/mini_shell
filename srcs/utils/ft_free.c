#include "../../minishell.h"

void	ft_free2d(char	**str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_free_lst(t_taken **taken)
{
	t_taken	*tmp;
	t_taken	*next;

	tmp = *taken;
	while (tmp != NULL)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
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
		if (tmp->redir != NULL)
			free(tmp->redir);
		if (tmp->path != NULL)
			free(tmp->path);
		free(tmp);
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
			ft_free2d(tmp->arg_cmd);
		free(tmp);
		tmp = next;
	}
}
