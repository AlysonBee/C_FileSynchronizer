/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 16:43:02 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/06 16:43:04 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int i;
	int	n;

	i = -1;
	n = len;
	if (dst > src)
	{
		while (--n >= 0)
			((char *)dst)[n] = ((char *)src)[n];
	}
	else if (src > dst)
	{
		while (++i <= (n - 1))
			((char *)dst)[i] = ((char *)src)[i];
	}
	return (dst);
}
