/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:29:56 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/08 16:31:42 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*news;

	i = -1;
	j = -1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	news = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (news == NULL)
		return (NULL);
	while (s1[++i] != '\0')
		news[i] = s1[i];
	while (s2[++j] != '\0')
	{
		news[i] = s2[j];
		i++;
	}
	news[i] = '\0';
	return (news);
}
