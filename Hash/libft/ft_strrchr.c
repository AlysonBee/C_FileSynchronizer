/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:50:07 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/17 11:20:35 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int i;
	int pos;

	pos = -1;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			pos = i;
		i++;
	}
	if (s[i] == c)
		pos = i;
	if (pos != -1)
		return ((char *)&s[pos]);
	return (NULL);
}
