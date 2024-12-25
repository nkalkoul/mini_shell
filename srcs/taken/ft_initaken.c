/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initaken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:03 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/24 20:36:40 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_initype(t_taken **taken)
{
	t_taken	*current;

	current = *taken;
	while (current ->next != NULL)
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

void	ft_check_cmd(t_taken **taken, t_cmd **cmd)
{
	t_taken	*current;
	t_cmd	*tmp;
	int		i;

	tmp = malloc(sizeof(t_cmd));
	current = *taken;
	if (current->next && current->type == REDIR)
	{
		tmp->redir = ft_strdup(current->token);
		tmp->files = ft_strdup(current->next->token);
	}
	else if (current->type == WORD)
	{
		i = 0;
		tmp->arg_cmd = malloc(sizeof(char *) * 5000);
		tmp->arg_cmd[i] = ft_strdup(current->token);
		while (current->next && current->next->type != PIPE )
		{
			tmp->arg_cmd[++i] = ft_strdup(current->next->token);
			current = current->next;
		}
		tmp->arg_cmd[++i] = NULL;
	}
	else
		tmp->pipe = ft_strdup(current->token);
	tmp->next = NULL;
	*cmd = tmp;
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

void	ft_initaken(t_taken **taken, char *rd, t_cmd **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	*taken = NULL;
	*cmd = NULL;
	while (rd[i])
	{
		while (rd[i] && ft_space(rd[i]) == 1)
			i++;
		if (rd[i])
		{
			j = ft_lst_ongbak(taken, rd + i);
			if (j == -1)
				return ;
			i = i + j;
		}
	}
	ft_initype(taken);
	ft_check_cmd(taken, cmd);
	ft_printaken((*taken));
	ft_printcmd(*cmd);
}
