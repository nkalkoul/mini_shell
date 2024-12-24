/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initaken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:03 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/24 00:24:43 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_initype(t_taken **taken)
{
	t_taken	*current;

	current = *taken;
	while (current != NULL)
	{
		if (current->token[0] == '|')
			current->type = PIPE;
		else if (current->token[0] == '>' || current->token[0] == '<')
			current->type = REDIR;
		else
			current->type = WORD;
		current = current->next;
	}
}

int	ft_findquote(char *src, int i)
{
	char	beefquot;

	beefquot = src[i];
	i++;
	while (src[i] && src[i] != beefquot)
		i++;
	return (i);
}

int	ft_lencopy(char *src)
{
	int		i;
	char	beefquot;

	i = 0;
	while (src[i])
	{
		if (ft_isoperator(src[0]) == 1)
		{
			while (src[i] == src[i + 1])
				i++;
			i++;
			return (i);
		}
		if (ft_isquote(src[i]) == 1)
			i = ft_findquote(src, i);
		if (ft_isoperator(src[i]) == 1)
			return (i);
		if (ft_isprint(src[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	ft_lst_ongbak(t_taken **taken, char *src)
{
	int		i;
	int		len;
	t_taken	*new;

	len = ft_lencopy(src);
	// if (ft_isquote(src[0]) == 1)
	// 	len++;
	new = malloc(sizeof(t_taken));
	if (!new)
		return (-1);
	new->token = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		new->token[i] = src[i];
	new->token[i] = '\0';
	new->next = NULL;
	ft_lstbackadd(taken, new);
	return (len);
}

void	ft_initaken(t_taken **taken, char *rd)
{
	int	i;

	i = 0;
	*taken = NULL;
	while (rd[i])
	{
		while (rd[i] && ft_space(rd[i]) == 1)
			i++;
		if (rd[i])
			i += ft_lst_ongbak(taken, rd + i);
	}
	ft_initype(taken);
	ft_printaken((*taken));
}
