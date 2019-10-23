/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:39:50 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 16:39:54 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	int i;

	i = -1;
	len++;
	if (ft_strlen(src) > 0)
	{
		while (src[++i] != '\0' && --len > 0)
		{
			dst[i] = src[i];
		}
		len++;
		while (--len > 1)
		{
			dst[i++] = '\0';
		}
	}
	else
		while (--len > 0)
			dst[++i] = '\0';
	return (dst);
}
