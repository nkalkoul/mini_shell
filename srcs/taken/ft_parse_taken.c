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

int	ft_token_to_word(t_taken *current, t_cmd **cmd)
{
	char	*tmp_cmd;

	tmp_cmd = strdup("");
	if (!tmp_cmd)
		return (1);  //  free tmp_cmd
	while (current->type == WORD)
	{
		tmp_cmd = ft_re_strjoin(tmp_cmd, current->token);
		tmp_cmd = ft_re_strjoin(tmp_cmd, " ");
		current = current->next;
	}
	(*cmd)->arg_cmd = ft_split(tmp_cmd, ' ');
	if ((*cmd)->arg_cmd == NULL)
		return (1);		//  free arg_cmd
	return (0);
}

int	ft_token_to_files(t_taken *current, t_cmd **cmd)
{
	(*cmd)->files = malloc(sizeof(t_files));
	if ((*cmd)->files == NULL)
		return (1);  // free lst_files
	(*cmd)->files->redir = ft_strdup(current->token);
	if ((*cmd)->files->redir == NULL)
		return (1);  // free redir  || free lst_files
	if (!current->next)
		return (1); // free redir  || free lst_files
	current = current->next;
	(*cmd)->files->path = ft_strdup(current->token);
	if ((*cmd)->files->path == NULL)
		return (1);  // free path  //  free redir  || free lst_files
	(*cmd)->files->next = NULL;
	// ft_lstadd_back()
	return (0);
}

int	ft_token_to_cmd(t_taken *current, t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (*cmd == NULL)
		return (1);   // free cmd
	if (current->type == REDIR)
	{
		if (ft_token_to_files(current, cmd) == 1)
			return (1);  
	}
	else if (current->type == WORD)
	{
		if (ft_token_to_word(current, cmd) == 1)
			return (1);  // free path   //  free redir
	}
	return (0);
}

int	ft_parse_lst_taken(t_taken **taken)
{
	t_taken	*current;
	t_cmd	**cmd;

	current = *taken;
	*cmd = NULL;
	if (current->type == PIPE)
		return (1);
	while (current != NULL)
	{
		if (current->type == PIPE)
			*cmd = (*cmd)->next;
		if (ft_check_operator(current) == 1)
			return (1);
		if (ft_token_to_cmd(current, cmd) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
