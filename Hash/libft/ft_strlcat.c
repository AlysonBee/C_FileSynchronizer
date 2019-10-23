/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/02 16:14:14 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/28 14:09:18 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		dstlen(char *dst, size_t *size)
{
	int	end;

	end = 0;
	while (dst[end] != '\0')
	{
		if (*size != 0)
		{
			(*size)--;
			end++;
		}
		else
			return (end);
	}
	return (end);
}

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	int			i;
	int			end;

	i = 0;
	end = dstlen(dst, &size);
	if (size == 0)
		return (end + ft_strlen(src));
	while (src[i] != '\0')
	{
		if (size-- != 1)
		{
			dst[end + i] = src[i];
			i++;
		}
		else
		{
			dst[end + i] = '\0';
			return (end + ft_strlen(src));
		}
	}
	if (src[i] == '\0')
		dst[end + i] = '\0';
	return (end + i);
}
