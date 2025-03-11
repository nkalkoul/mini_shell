#include "../../minishell.h"

int	ft_operator_to_cmd(t_cmd **tmp, t_taken **current)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (1);
	new->type = (*current)->type;
	ft_lstbackadd_cmd(tmp, new);
	(*current) = (*current)->next;
	return (0);
}

t_cmd	*ft_parse_lst_taken(t_taken *taken)
{
	t_taken	*current;
	t_cmd	*cmd;

	if (ft_check_error_parse(taken) == 1)
		return (NULL);
	current = taken;
	cmd = NULL;
	while (current != NULL)
	{
		if (ft_token_to_cmd(&current, &cmd) == 1)
			return (ft_free_files(&(cmd)->files), ft_free_cmd(cmd), NULL);
		else if (current && (current->type == PIPE
				|| current->type == OR || current->type == AND))
		{
			if (ft_operator_to_cmd(&cmd, &current) == 1)
				return (ft_free_files(&(cmd)->files), ft_free_cmd(cmd), NULL);
		}
	}
	ft_printf("cmd = ");
	ft_printcmd(cmd);
	return (cmd);
}
