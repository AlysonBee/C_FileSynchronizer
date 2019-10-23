/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:45:28 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/31 11:09:34 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	int		n;
	int		s_len;
	int		i;

	n = (int)len + 1;
	i = -1;
	s_len = ft_strlen(little);
	if (!*little)
		return ((char *)big);
	while (big[++i] && --n > 0)
		if (big[i] == *little && n >= s_len)
			if (ft_strncmp(big + i, little, s_len) == 0)
				return ((char *)(big + i));
	return (NULL);
}
