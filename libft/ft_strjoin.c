/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: modavid <modavid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 03:54:32 by nas91             #+#    #+#             */
/*   Updated: 2025/02/02 20:57:18 by modavid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	sizn;
	size_t	sizs1;
	size_t	sizs2;

	sizs1 = ft_strlen(s1);
	sizs2 = ft_strlen(s2);
	sizn = sizs1 + sizs2;
	if (sizn < 1)
	{
		new = ft_malloc(1);
		if (new == NULL)
			return (NULL);
		new[0] = 0;
	}
	else
	{
		new = ft_malloc(sizeof(char) * (sizn + 1));
		if (new == NULL)
			return (NULL);
		ft_strlcpy(new, s1, sizs1 + 1);
		ft_strlcat(new, s2, sizn + 1);
	}
	return (new);
}
