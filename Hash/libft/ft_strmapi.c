/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 14:58:26 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 16:53:24 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*temp;
	char	*news;
	int		i;

	i = -1;
	if (s != NULL)
	{
		temp = ft_strnew(ft_strlen(s));
		if (temp == NULL)
			return (NULL);
		while (s[++i] != '\0')
			temp[i] = f(i, ((char *)s)[i]);
		i = -1;
		news = ft_strnew(ft_strlen(temp));
		if (news == NULL)
			return (NULL);
		while (temp[++i] != '\0')
			news[i] = temp[i];
		return (news);
	}
	return (NULL);
}
