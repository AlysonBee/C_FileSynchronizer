/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:29:22 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 16:29:27 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	int i;

	i = -1;
	if (ft_strlen(src) > 0)
		while (src[++i] != '\0')
		{
			dst[i] = src[i];
		}
	else
		dst[0] = '\0';
	dst[i] = '\0';
	return (dst);
}
