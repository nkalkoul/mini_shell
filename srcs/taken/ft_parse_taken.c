#include "../../minishell.h"

int	ft_check_operator(t_taken *current)
{
	if (current->token[0] == '>' && current->token[1] == '>'
		&& current->token[2] == '>')
		return (1);
	if (current->token[0] == '<' && current->token[1] == '<'
		&& current->token[2] == '<')
		return (1);
	if (current->token[0] == '|' && current->token[1] == '|')
		return (1);
	return (0);
}

int	ft_token_to_word(t_taken **current, t_cmd **cmd)
{
	char	*tmp_cmd;

	tmp_cmd = strdup("");
	if (!tmp_cmd)
		return (1);		//  free tmp_cmd
	while (*current != NULL && (*current)->type == WORD)
	{
		tmp_cmd = ft_re_strjoin(tmp_cmd, (*current)->token);
		tmp_cmd = ft_re_strjoin(tmp_cmd, " ");
		*current = (*current)->next;
	}
	printf("\n\ntmp cmd ====== %s\n\n", tmp_cmd);
	(*cmd)->arg_cmd = ft_split(tmp_cmd, ' ');
	if ((*cmd)->arg_cmd == NULL)
		return (1);		//  free arg_cmd
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
	ft_lstbackadd_files((*cmd)->files, new);
	return (0);
}

int	ft_token_to_cmd(t_taken **current, t_cmd **cmd)
{
	if ((*current)->type == REDIR)
	{
		if (ft_token_to_files(current, cmd) == 1)
			return (1);
	}
	else if ((*current)->type == WORD)
	{
		if (ft_token_to_word(current, cmd) == 1)
			return (1); 	 // free path   //  free redir
	}
	(*cmd)->next = NULL;
	return (0);
}

int	ft_parse_lst_taken(t_taken **taken, t_cmd **cmd)
{
	t_taken	*current;
	t_cmd	*new;
	t_cmd	*tmp;

	current = *taken;
	*cmd = NULL;
	if (current->type == PIPE)
		return (1);
	*cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (1);
	*(*cmd)->files = NULL;
	tmp = *cmd;
	while (current != NULL)
	{
		if (ft_check_operator(current) == 1)
			return (1);
		if (ft_token_to_cmd(&current, &tmp) == 1)
			return (1);
		if (current && current->type == PIPE)
		{
			new = malloc(sizeof(t_cmd));
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
