/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:20:35 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 12:14:06 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_parse_redir(char *rd)
{
	int	i;
	int	count;

	i = 0;
	while (rd[i])
	{
		count = 0;
		if (ft_isquote(rd[i]) == 1)
		{
			i++;
			while (ft_isquote(rd[i]) == 0)
				i++;
		}
		while (ft_isredir(rd[i]) == 1)
		{
			count++;
			i++;
		}
		if (count > 2)
			return (1);
		if (rd[i])
			i++;
	}
	return (0);
}

int	ft_parse_quote(char *rd)
{
	int	i;

	i = 0;
	while (rd[i])
	{
		if (ft_isdouble(rd[i]) == 0)
		{
			i++;
			while (rd[i] && ft_isdouble(rd[i]) == 1)
				i++;
			if (rd[i] == '\0')
				return (1);
		}
		if (ft_isimple(rd[i]) == 0)
		{
			i++;
			while (rd[i] && ft_isimple(rd[i]) == 1)
				i++;
			if (rd[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_errormsg(int m)
{
	if (m == 1)
		ft_printf(2, "shell : syntax error near unexpected token 'newline'\n");
	if (m == 2)
		ft_printf(2, "shell : syntax error near unexpected token '>'\n");
	if (m == 3)
		ft_printf(2, "shell : syntax error near unexpected token '|'\n");
}

int	ft_check_first_error(t_taken *current)
{
	if (current->token[0] == '&' && current->next->token[0] == '|')
		return (ft_errormsg(3), 1);
	if (current->token[0] == '|' && current->next->token[0] == '&')
		return (ft_errormsg(3), 1);
	return (0);
}

int	ft_check_error_parse(t_taken *current)
{
	while (current != NULL)
	{
		if (ft_check_first_error(current) == 1)
			return (1);
		if (current->type == PIPE && (current->next == NULL
				|| current->next->type == PIPE))
			return (ft_errormsg(3), 1);
		if (current->token[0] == '|' && current->token[1] == '|'
			&& current->token[2] == '|')
			return (ft_errormsg(3), 1);
		if (current->token[0] == '>' && current->token[1] == '>'
			&& current->token[2] == '>')
			return (ft_errormsg(2), 1);
		if (current->token[0] == '<' && current->token[1] == '<'
			&& current->token[2] == '<')
			return (ft_errormsg(1), 1);
		if ((current->type == REDIRDD || current->type == REDIRGG
				|| current->type == REDIRD || current->type == REDIRG)
			&& (current->next == NULL || current->next->type != WORD))
			return (ft_errormsg(1), 1);
		current = current->next;
	}
	return (0);
}
