/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:01:51 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/17 14:04:24 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*cdst;
	char	*csrc;

	cdst = dst;
	csrc = (char *)src;
	i = -1;
	while (++i < (int)n)
		*(cdst + i) = *(csrc + i);
	return (dst);
}
