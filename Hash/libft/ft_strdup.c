/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:59:31 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 16:55:30 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*stemp;

	stemp = malloc(ft_strlen(s1) + 1);
	if (stemp == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
	{
		stemp[i] = s1[i];
	}
	stemp[i] = '\0';
	return (stemp);
}
