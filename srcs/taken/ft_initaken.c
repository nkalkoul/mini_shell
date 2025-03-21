/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initaken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:03 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/17 22:06:50 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_initype(t_taken *taken)
{
	t_taken	*current;

	current = taken;
	while (current != NULL)
	{
		if (current->token[0] == '|' && current->token[1] == '|')
			current->type = OR;
		else if (current->token[0] == '|')
			current->type = PIPE;
		else if (current->token[0] == '>' && current->token[1] == '>')
			current->type = REDIRDD;
		else if (current->token[0] == '<' && current->token[1] == '<')
			current->type = REDIRGG;
		else if (current->token[0] == '>')
			current->type = REDIRD;
		else if (current->token[0] == '<')
			current->type = REDIRG;
		else if (current->token[0] == '&' && current->token[1] == '&')
			current->type = AND;
		else
			current->type = WORD;
		current = current->next;
	}
	return (0);
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

	i = 0;
	while (src[i])
	{
		if (ft_isoperator(src[0]) == 1 || (src[0] == '&' && src[1] == '&'))
		{
			while (src[i] == src[i + 1])
				i++;
			i++;
			return (i);
		}
		if (ft_isquote(src[i]) == 1)
			i = ft_findquote(src, i);
		if (ft_isoperator(src[i]) == 1 || (src[i] == '&' && src[i + 1] == '&'))
			return (i);
		if (src[i] == ' ' || src[i] == '\t')
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
	new = ft_malloc(sizeof(t_taken));
	if (!new)
		return (ft_free_lst(taken), -1);
	new->token = ft_malloc(sizeof(char) * (len + 1));
	if (!new->token)
		return (ft_free(new), ft_free(taken), -1);
	i = -1;
	while (++i < len)
		new->token[i] = src[i];
	new->token[i] = '\0';
	new->next = NULL;
	ft_lstbackadd(taken, new);
	return (len);
}

t_taken	*ft_initaken(char *rd)
{
	t_taken	*taken;
	int		i;
	int		j;

	j = 0;
	i = 0;
	taken = NULL;
	if (ft_parse_quote(rd) == 1)
		return (ft_putendl_fd("Quote not closed", 1), NULL);
	while (rd[i])
	{
		while (rd[i] && ft_space(rd[i]) == 1)
			i++;
		if (rd[i])
		{
			j = ft_lst_ongbak(&taken, rd + i);
			if (j == -1)
				return (NULL);
			i = i + j;
		}
	}
	if (ft_initype(taken) == 1)
		return (ft_free(((void *) -1)), NULL);
	return (taken);
}
