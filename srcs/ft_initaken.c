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

#include "../minishell.h"

void	ft_printaken(t_taken *taken)
{
	t_taken	*curent;

	curent = taken;
	while (curent != NULL)
	{
		ft_printf(" chaine = == %s§\n", curent->token);
		curent = curent->next;
	}
}

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

void	ft_lstbackadd(t_taken **lst, t_taken *new)
{
	t_taken	*temp;

	if ((*lst) == NULL)
	{
		(*lst) = new;
		return ;
	}
	temp = *lst;
	while (temp -> next != NULL)
		temp = temp -> next;
	temp -> next = new;
}

int	ft_lst_ongbak(t_taken **taken, char *src, char fin)
{
	int		i;
	int		len;
	t_taken	*new;

	i = 0;
	new = malloc(sizeof(t_taken));
	if (!new)
		return (-1);
	while (src[i + 1] && src[i + 1] != fin)
		i++;
	len = i + 1;
	if ((fin == '\'' || fin == '"') && (src[0] == '\'' || src[0] == '"'))
		len = i + 2;
	if (src[0] == '|' || src[0] == '>' || src[0] == '<')
		len = 1;
	if ((src[0] == '>' && src[1] == '>') || (src[0] == '<' && src[1] == '<'))
		len = 2;
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
	while (src[i] && ft_isprint(src[i]) == 1 && src[i] != '|'
		&& src[i] != '"' && src[i] != '\'' && src[i] != '>' && src[i] != '<')
		i++;
	return (ft_lst_ongbak(taken, src, src[i]));
}

int	ft_space(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
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
