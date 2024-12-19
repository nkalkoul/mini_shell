/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initaken.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 23:21:03 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/19 01:27:14 by nkalkoul         ###   ########.fr       */
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

int	ft_lst_ongbak(t_taken **taken, char *src, char fin)
{
	int		i;
	t_taken	*new;
	t_taken	*current;

	i = 0;
	printf("fin = %c\n", fin);
	new = malloc(sizeof(t_taken));
	while (src[i] != fin)
		i++;
	new->token = malloc(sizeof(char) * (i + 1));
	i = -1;
	while (src[++i] != fin)
		new->token[i] = src[i];
	new->token[i] = '\0';
	new->next = NULL;
	if (*taken == NULL)
	{
		*taken = new;
		return (i);
	}
	current = *taken;
	while (current->next != NULL)
		current = current->next;
	current->next = new;
	return (i);
}

//il est le test

int	ft_copy_rd(t_taken **taken, char *src)
{
	int		i;

	i = 0;
	if (src[i] == '"' || src[i] == 44)
		return (ft_lst_ongbak(taken, src + 1, src[i]) + 2);
	while (src[i] && ft_isprint(src[i]) == 1)
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
	ft_printaken((*taken));
}
