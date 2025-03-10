#include "../../minishell.h"

int	ft_check_error_parse(t_taken *current)
{
	if (current && current->type == PIPE
		&& current->type == OR && current->type == AND)
		return (1);
	while (current != NULL)
	{
		if (current->type == PIPE && (current->next == NULL
			|| current->next->type == PIPE))
			return (1);
		if (current->token[0] == '|' && current->token[1] == '|'
			&& current->token[2] == '|')
			return (1);
		if (current->token[0] == '>' && current->token[1] == '>'
			&& current->token[2] == '>')
			return (1);
		if (current->token[0] == '<' && current->token[1] == '<'
			&& current->token[2] == '<')
			return (1);
		if ((current->type == REDIRDD || current->type == REDIRGG
			|| current->type == REDIRD || current->type == REDIRG)
			&& (current->next == NULL || current->next->type != WORD))
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_count_word(t_taken **current)
{
	int		i;
	t_taken	*tmp;

	i = 0;
	tmp = *current;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIRDD || tmp->type == REDIRGG
			|| tmp->type == REDIRD || tmp->type == REDIRG)
			tmp = tmp->next;
		else if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_token_to_word(t_taken **current, t_cmd **cmd)
{
	int		i;
	t_taken	*tmp;

	(*cmd)->arg_cmd = ft_malloc(sizeof(char *) * (ft_count_word(current) + 1));
	if ((*cmd)->arg_cmd == NULL)
		return (1);
	tmp = *current;
	i = 0;
	while (tmp && tmp->type != PIPE
		&& tmp->type != OR && tmp->type != AND)
	{
		if (tmp->type == REDIRDD || tmp->type == REDIRGG
			|| tmp->type == REDIRD || tmp->type == REDIRG)
			tmp = tmp->next;
		else if (tmp->type == WORD)
		{
			(*cmd)->arg_cmd[i] = ft_strdup(tmp->token);
			if ((*cmd)->arg_cmd[i] == NULL)
				return (1);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd)->arg_cmd[i] = NULL;
	return (0);
}

int	ft_token_to_files(t_taken **current, t_cmd *cmd)
{
	t_files	*new;

	new = ft_calloc(1, sizeof(t_files));
	if (new == NULL)
		return (1);
	new->type = (*current)->type;
	if (!(*current)->next)
		return (1);
	*current = (*current)->next;
	new->path = ft_strdup((*current)->token);
	if (new->path == NULL)
		return (1);
	new->next = NULL;
	if (new->type == REDIRGG)
		new->heredoc_content = ft_newread(new);
	ft_lstbackadd_files(&cmd->files, new);
	return (0);
}

int	ft_token_to_cmd(t_taken **current, t_cmd **cmd)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	while (*current && (*current)->type != PIPE
		&& (*current)->type != OR && (*current)->type != AND)
	{
		if ((*current)->type == REDIRDD || (*current)->type == REDIRGG
			|| (*current)->type == REDIRD || (*current)->type == REDIRG)
		{
			if (ft_token_to_files(current, new) == 1)
				return (1);
		}
		else if ((*current)->type == WORD && new->arg_cmd == NULL)
		{
			if (ft_token_to_word(current, &new) == 1)
				return (1);
		}
		*current = (*current)->next;
	}
	ft_lstbackadd_cmd(cmd, new);
	return (0);
}

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
