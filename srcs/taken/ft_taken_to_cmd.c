#include "../../minishell.h"

int	ft_check_error_parse(t_taken *current)
{
	if (current->type == PIPE && current->type == OR && current->type == AND)
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
		if (current->type == REDIR && (current->next == NULL
				|| current->next->type != WORD))
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
		if (tmp->type == REDIR)
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

	(*cmd)->arg_cmd = malloc(sizeof(char *) * (ft_count_word(current) + 1));
	if ((*cmd)->arg_cmd == NULL)
		return (1);
	tmp = *current;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
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

int	ft_token_to_files(t_taken **current, t_cmd **cmd)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (new == NULL)
		return (1);
	new->redir = ft_strdup((*current)->token);
	if (new->redir == NULL)
		return (1);
	if (!(*current)->next)
		return (1);
	*current = (*current)->next;
	new->path = ft_strdup((*current)->token);
	if (new->path == NULL)
		return (1);
	new->next = NULL;
	ft_lstbackadd_files(&((*cmd)->files), new);
	return (0);
}

int	ft_token_to_cmd(t_taken **current, t_cmd **cmd)
{
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == REDIR)
		{
			if (ft_token_to_files(current, cmd) == 1)
				return (1);
		}
		else if ((*current)->type == WORD && (*cmd)->arg_cmd == NULL)
		{
			if (ft_token_to_word(current, cmd) == 1)
				return (1);
		}
		*current = (*current)->next;
	}
	(*cmd)->next = NULL;
	return (0);
}

t_cmd	*ft_parse_lst_taken(t_taken *taken)
{
	t_taken	*current;
	t_cmd	*cmd;
	t_cmd	*tmp;
	t_cmd	*new;

	if (ft_check_error_parse(taken) == 1)
		return (NULL);
	current = taken;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	tmp = cmd;
	while (current != NULL)
	{
		if (ft_token_to_cmd(&current, &tmp) == 1)
			return (ft_free_files(&(cmd)->files), ft_free_cmd(cmd), NULL);
		else if (current && current->type == PIPE)
		{
			new = ft_calloc(1, sizeof(t_cmd));
			if (!new)
				return (ft_free_files(&(cmd)->files), ft_free_cmd(cmd), NULL);
			ft_lstbackadd_cmd(&tmp, new);
			tmp = tmp->next;
			current = current->next;
		}
	}
	ft_printcmd(cmd);
	return (cmd);
}
