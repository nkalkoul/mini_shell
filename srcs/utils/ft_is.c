/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 08:31:55 by nas91             #+#    #+#             */
/*   Updated: 2025/03/16 11:17:04 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}

int	ft_isquote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

int	ft_isredir(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

int	ft_isoperator(char c)
{
	if (c == '|' || ft_isredir(c) == 1)
		return (1);
	return (0);
}
