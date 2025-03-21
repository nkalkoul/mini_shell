/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_taken_to_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:09:26 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:09:27 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	ft_token_to_files(t_taken **current, t_cmd *cmd, t_global *g)
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
	{
		new->heredoc_content = ft_newread(new, g);
		if (new->heredoc_content == NULL)
			return (1);
	}
	ft_lstbackadd_files(&cmd->files, new);
	return (0);
}

int	ft_token_to_cmd(t_taken **current, t_cmd **cmd, t_global *g)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	while (*current && (*current)->type != PIPE
		&& (*current)->type != OR && (*current)->type != AND)
	{
		if ((*current)->type == REDIRDD || (*current)->type == REDIRGG
			|| (*current)->type == REDIRD || (*current)->type == REDIRG)
		{
			if (ft_token_to_files(current, new, g) == 1)
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
