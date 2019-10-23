/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:35:46 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/17 14:05:31 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int		i;
	char	*cdst;
	char	*csrc;

	cdst = dst;
	csrc = (char *)src;
	i = -1;
	while (++i < (int)n)
	{
		*(cdst + i) = *(csrc + i);
		if (*((unsigned char *)csrc + i) == (unsigned char)c)
			return (dst + i + 1);
	}
	return (NULL);
}
