/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 11:07:19 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 11:09:52 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*ig;
	unsigned char	*ih;

	ig = (void *)s1;
	ih = (void *)s2;
	i = 0;
	n++;
	while (--n > 0)
	{
		if (ig[i] != ih[i])
		{
			return (ig[i] - ih[i]);
		}
		i++;
	}
	return (0);
}
