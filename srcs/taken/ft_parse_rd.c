/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:20:35 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/24 16:24:37 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isimple(char rd)
{
	if (rd == '\'')
		return (0);
	return (1);
}

int	ft_isdouble(char rd)
{
	if (rd == '"')
		return (0);
	return (1);
}

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

int	ft_parse_rd(char *rd)
{
	if (ft_parse_quote(rd) == 1)
		return (ft_putendl_fd("Quote not closed", 1), 1);
	// if (ft_parse_redir(rd) == 1)
	// 	return (ft_putendl_fd("too many redir a la suite", 1), 1);
	return (0);
}
