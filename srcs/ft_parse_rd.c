/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_rd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 00:20:35 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/20 00:35:05 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_parse_quote(char rd)
{
	if (rd == '\'')
		return (0);
	return (1);
}

int	ft_parse_doublequote(char rd)
{
	if (rd == '"')
		return (0);
	return (1);
}

int	ft_parse_rd(char *rd)
{
	int	i;

	i = 0;
	while (rd[i])
	{
		if (ft_parse_doublequote(rd[i]) == 0)
		{
			i++;
			while (rd[i] && ft_parse_doublequote(rd[i]) == 1)
				i++;
			if (rd[i] == '\0')
				return (1);
		}
		if (ft_parse_quote(rd[i]) == 0)
		{
			i++;
			while (rd[i] && ft_parse_quote(rd[i]) == 1)
				i++;
			if (rd[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
