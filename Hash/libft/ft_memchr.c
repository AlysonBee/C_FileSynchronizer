/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:59:18 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 10:00:16 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*ss;

	ss = (unsigned char *)s;
	i = -1;
	n++;
	while (--n > 0)
		if (ss[++i] == (unsigned char)c)
			return (&(ss)[i]);
	return (NULL);
}
