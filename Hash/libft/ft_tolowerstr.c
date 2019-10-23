/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:05:10 by gsferopo          #+#    #+#             */
/*   Updated: 2017/09/04 11:22:58 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_tolowerstr(char *c)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_strdup(c);
	while (++i <= (int)ft_strlen(c))
		if ('A' <= c[i] && c[i] <= 'Z')
			str[i] = c[i] + 32;
	return (str);
}
