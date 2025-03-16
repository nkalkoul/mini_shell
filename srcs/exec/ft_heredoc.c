/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 11:07:39 by nkalkoul          #+#    #+#             */
/*   Updated: 2025/03/16 11:07:40 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_printerrord(int i, char *f)
{
	ft_printf(2, "mouniashell: warning: here-document at ligne %d", i);
	ft_printf(2, " delimited by end-of-file (wanted'%s')\n", f);
}

char	**ft_addtab(char **tab, char *red)
{
	char	**new;
	int		i;

	i = 0;
	if (!tab)
	{
		tab = ft_malloc(sizeof(char *) * 1);
		tab[0] = 0;
	}
	new = ft_malloc(sizeof(char *) * (ft_countdouble(tab) + 2));
	if (!new)
		return (NULL);
	while (tab[i])
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = ft_strdup(red);
	new[++i] = 0;
	return (new);
}

char	**ft_newread(t_files *files, t_global *g)
{
	char	**redir;
	char	*red;
	int		i;

	i = 0;
	redir = NULL;
	while (++i)
	{
		red = readline("heredoc> ");
		if (g_sign != 0)
		{
			g->status = g_sign;
			g_sign = 0;
			return (NULL);
		}
		if (red == NULL)
		{
			ft_printerrord(i, files->path);
			break ;
		}
		if (ft_strcmp(files->path, red) == 0)
			break ;
		redir = ft_addtab(redir, red);
	}
	return (redir);
}
