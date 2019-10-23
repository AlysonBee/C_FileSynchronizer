/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 09:17:29 by gsferopo          #+#    #+#             */
/*   Updated: 2017/11/13 14:32:19 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strend(char *dst, char *src)
{
	int		i;
	int		j;
	char	*news;

	i = -1;
	j = -1;
	if (dst == NULL || src == NULL)
		return (NULL);
	news = ft_strnew(ft_strlen(dst) + ft_strlen(src));
	if (news == NULL)
		return (NULL);
	while (dst[++i] != '\0')
		news[i] = dst[i];
	while (src[++j] != '\0')
	{
		news[i] = src[j];
		i++;
	}
	news[i] = '\0';
	free(dst);
	dst = news;
	return (dst);
}
