/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:22:40 by modavid           #+#    #+#             */
/*   Updated: 2025/03/17 16:00:26 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_first_error(t_taken *current)
{
	if (current->type == PIPE)
		return (ft_errormsg(4), 1);
	if (current->type == OR)
		return (ft_errormsg(4), 1);
	if (current->type == AND)
		return (ft_errormsg(5), 1);
	return (0);
}

int	ft_check_redir(t_taken *current)
{
	if (current->type == REDIRD && (current->next->type == REDIRGG
			|| current->next->type == REDIRD || current->next->type == PIPE
			|| current->next->type == AND || current->next->type == REDIRDD
			|| current->next->type == REDIRG || current->next->type == OR))
		return (ft_errormsg(2), 1);
	if (current->type == REDIRDD && (current->next->type == REDIRGG
			|| current->next->type == REDIRD || current->next->type == PIPE
			|| current->next->type == AND || current->next->type == REDIRDD
			|| current->next->type == REDIRG || current->next->type == OR))
		return (ft_errormsg(2), 1);
	if (current->type == REDIRGG && (current->next->type == REDIRGG
			|| current->next->type == REDIRD || current->next->type == PIPE
			|| current->next->type == AND || current->next->type == REDIRDD
			|| current->next->type == REDIRG || current->next->type == OR))
		return (ft_errormsg(3), 1);
	if (current->type == REDIRG && (current->next->type == REDIRGG
			|| current->next->type == REDIRD || current->next->type == PIPE
			|| current->next->type == AND || current->next->type == REDIRDD
			|| current->next->type == REDIRG || current->next->type == OR))
		return (ft_errormsg(3), 1);
	return (0);
}

int	ft_check_redirfirst(t_taken *current)
{
	if ((current->type == REDIRD || current->type == REDIRDD
			|| current->type == REDIRG || current->type == REDIRGG)
		&& !current->next)
		return (ft_errormsg(1), 1);
	if (ft_strlen(current->token) > 2)
	{
		if (current->token[0] == '|' && current->token[1] == '|'
			&& current->token[2] == '|')
			return (ft_errormsg(4), 1);
		if (current->token[0] == '>' && current->token[1] == '>'
			&& current->token[2] == '>')
			return (ft_errormsg(2), 1);
		if (current->token[0] == '<' && current->token[1] == '<'
			&& current->token[2] == '<')
			return (ft_errormsg(3), 1);
		if (current->token[0] == '&' && current->token[1] == '&'
			&& current->token[2] == '&')
			return (ft_errormsg(5), 1);
	}
	return (0);
}

int	ft_check_second_noob(t_taken *current)
{
	if (current->type == PIPE && current->next == NULL)
		return (ft_errormsg(4), 1);
	if (current->type == OR && current->next == NULL)
		return (ft_errormsg(4), 1);
	if (current->type == AND && current->next == NULL)
		return (ft_errormsg(5), 1);
	return (0);
}

int	ft_check_second_operator(t_taken *current)
{
	if (current->token[0] == '&' && current->token[1] == '\0')
		return (ft_errormsg(5), 1);
	if (current->type == PIPE && (current->next->type == PIPE
			|| current->next->type == OR || current->next->type == AND))
		return (ft_errormsg(4), 1);
	if (current->type == AND && (current->next->type == PIPE
			|| current->next->type == OR || current->next->type == AND))
		return (ft_errormsg(5), 1);
	if (current->type == OR && (current->next->type == PIPE
			|| current->next->type == OR || current->next->type == AND))
		return (ft_errormsg(4), 1);
	return (0);
}
