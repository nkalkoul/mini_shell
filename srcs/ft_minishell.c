/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/26 00:49:38 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*rd;
	t_taken	*taken;

	while (1)
	{
		rd = readline("Mouninashell :");
		add_history(rd);
		if (ft_parse_rd(rd) == 1)
			ft_putendl_fd("Error", 1);
		else
		{
			if (ft_initaken(&taken, rd) == 1)
				return (ft_putendl_fd("Error Parsing", 2), 1);
		}
	}
	ft_free_lst(&taken);
	return (0);
}
