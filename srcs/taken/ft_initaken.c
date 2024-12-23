/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initaken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:03 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/21 20:24:46 by modavid          ###   ########.fr       */
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

int	ft_lencopy(char *src, char fin)
{
	int	i;

	i = 1;
	while (src[i] && src[i] != fin)
	{
		if (ft_isquote(fin) == 0 && src[0] == fin)
		{
			if (ft_isquote(src[i]) == 1)
			{
				while (ft_isquote(src[++i]) == 0)
					i++;
			}
			if (ft_isoperator(src[0]) == 0 && ft_isoperator(src[i]) == 1)
				return (i);
			if (ft_isoperator(src[i]) == 1)
			{
				while (ft_isoperator(src[i]) == 1)
					i++;
				return (i);
			}
		}
		i++;
	}
	return (i);
}

	// i = i + 1;
	// if ((fin == '\'' || fin == '"'))
	// 	i = i + 2;
	// if (src[0] == '|' || src[0] == '>' || src[0] == '<')
	// 	i = 1;
	// if ((src[0] == '>' && src[1] == '>') || (src[0] == '<' && src[1] == '<'))
	// 	i = 2;
int	ft_lst_ongbak(t_taken **taken, char *src, char fin)
{
	int		i;
	int		len;
	t_taken	*new;

	len = ft_lencopy(src, fin);
	if (ft_isquote(fin) == 1 && src[0] == fin)
		len++;
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

int	ft_copy_rd(t_taken **taken, char *src)
{
	int		i;

	i = 0;
	if (src[i] == '"' || src[i] == 44)
		return (ft_lst_ongbak(taken, src, src[i]));
	while (src[i] && ft_isprint(src[i]) == 1)
		i++;
	return (ft_lst_ongbak(taken, src, src[i]));
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
			i += ft_copy_rd(taken, rd + i);
	}
	ft_initype(taken);
	ft_printaken((*taken));
}
