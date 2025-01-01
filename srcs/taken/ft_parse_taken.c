#include "../../minishell.h"

int	ft_check_error_parse(t_taken *current)
{
	if (current->type == PIPE)
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

int	ft_token_to_word(t_taken **current, t_cmd **cmd)
{
	int		i;
	t_taken	*tmp;

	tmp = *current;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
			tmp = tmp->next;
		else if (tmp->type == WORD)
			i++;
		tmp = tmp->next;
	}
	(*cmd)->arg_cmd = malloc(sizeof(char *) * (i + 1));
	if ((*cmd)->arg_cmd == NULL)
		return (1);		// free
	tmp = *current;
	i = 0;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR)
			tmp = tmp->next;
		else if (tmp->type == WORD)
		{
			(*cmd)->arg_cmd[i] = ft_strdup(tmp->token);
			i++;
		}
		tmp = tmp->next;
	}
	(*cmd)->arg_cmd[i] = NULL;
	*current = (*current)->next;
	return (0);
}

int	ft_token_to_files(t_taken **current, t_cmd **cmd)
{
	t_files	*new;

	new = malloc(sizeof(t_files));
	if (new == NULL)
		return (1);			// free lst_files
	new->redir = ft_strdup((*current)->token);
	if (new->redir == NULL)
		return (1);			// free redir  || free lst_files
	if (!(*current)->next)
		return (1);			// free redir  || free lst_files
	*current = (*current)->next;
	new->path = ft_strdup((*current)->token);
	if (new->path == NULL)
		return (1); 		// free path  //  free redir || free lst_files
	new->next = NULL;
	*current = (*current)->next;
	ft_lstbackadd_files(&((*cmd)->files), new);
	return (0);
}

int	ft_token_to_cmd(t_taken **current, t_cmd **cmd)
{
	if ((*current)->type == REDIR)
	{
		if (ft_token_to_files(current, cmd) == 1)
			return (1);
	}
	else if ((*current)->type == WORD && (*cmd)->arg_cmd == NULL)
	{
		if (ft_token_to_word(current, cmd) == 1)
			return (1); 	 // free path   //  free redir
	}
	(*cmd)->next = NULL;
	return (0);
}

int	ft_parse_lst_taken(t_taken *taken, t_cmd **cmd)
{
	t_taken	*current;
	t_cmd	*new;
	t_cmd	*tmp;

	current = taken;
	if (ft_check_error_parse(current) == 1)
		return (1);
	*cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (1);
	// printf("files %p\n", *files);
	tmp = *cmd;
	while (current != NULL)
	{
		if (ft_token_to_cmd(&current, &tmp) == 1)
			return (1);
		ft_printfiles(tmp);
		if (current && current->type == PIPE)
		{
			new = ft_calloc(1, sizeof(t_cmd));
			if (!new)
				return (1);	// free new & path & redir
			ft_lstbackadd_cmd(&tmp, new);
			tmp = tmp->next;
			current = current->next;
		}
	}
	ft_printcmd(*cmd);
	return (0);
}
