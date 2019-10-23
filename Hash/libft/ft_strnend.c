/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnend.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 09:18:02 by gsferopo          #+#    #+#             */
/*   Updated: 2017/10/04 09:18:03 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnend(char *dst, const char *src, int n)
{
	char	*nstr;

	n++;
	nstr = (char *)malloc(sizeof(char) * (ft_strlen(dst) + n));
	ft_bzero(nstr, ft_strlen(dst) + n);
	ft_strcpy(nstr, dst);
	ft_strlcat(nstr, src, n + ft_strlen(dst));
	free(dst);
	return (nstr);
}
