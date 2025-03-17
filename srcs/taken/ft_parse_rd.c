/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:20:35 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 16:01:13 by modavid          ###   ########.fr       */
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
		ft_printf(2, "shell : syntax error near unexpected token '<'\n");
	if (m == 4)
		ft_printf(2, "shell : syntax error near unexpected token '|'\n");
	if (m == 5)
		ft_printf(2, "shell : syntax error near unexpected token '&'\n");
}

int	ft_check_error_parse(t_taken *current)
{
	if (ft_check_first_error(current) == 1)
		return (1);
	while (current)
	{
		if (ft_check_redirfirst(current) == 1)
			return (1);
		if (ft_check_second_noob(current) == 1)
			return (1);
		if (ft_check_second_operator(current) == 1)
			return (1);
		if (ft_check_redir(current) == 1)
			return (1);
		current = current->next;
	}
	return (0);
}
