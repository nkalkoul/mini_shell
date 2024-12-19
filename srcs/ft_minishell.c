/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkalkoul <nkalkoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:10:38 by nkalkoul          #+#    #+#             */
/*   Updated: 2024/12/20 00:40:40 by nkalkoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*rd;
	t_taken	*taken;

	rd = readline("Mouninashell :");
	if (ft_parse_rd(rd) == 1)
		return (ft_putendl_fd("Error Parsing", 1), 1);
	ft_initaken(&taken, rd);
	return (0);
}
