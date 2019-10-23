/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 15:19:28 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 17:11:15 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	int		i;
	int		j;
	char	*news;

	j = 0;
	if (s != NULL && &s[start] != NULL)
	{
		i = start - 1;
		news = ft_strnew(len);
		if (news == NULL)
			return (NULL);
		while (s[++i] != '\0' && len-- > 0)
			news[j++] = s[i];
		news[i] = '\0';
		return (news);
	}
	return (NULL);
}
