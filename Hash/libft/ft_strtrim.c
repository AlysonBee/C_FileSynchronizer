/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:44:39 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/24 13:48:58 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	getse(char const *s, int i, int *start, int *end)
{
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	*start = i;
	while ((s[*end] == ' ' || s[*end] == '\n' || s[*end] == '\t' ||
				s[*end] == '\0') && *end > 0)
		(*end)--;
}

char		*ft_strtrim(char const *s)
{
	char	*news;
	int		i;
	int		start;
	int		end;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (s[0] == '\0')
		return ((char *)s);
	end = ft_strlen(s);
	getse(s, i, &start, &end);
	start--;
	i = -1;
	news = ft_strnew(ft_clamp(1, end - start, end - start));
	if (news == NULL)
		return (NULL);
	if (end == 0 && (news[0] = '\0') != '\t')
		return (news);
	while (++start < end + 1)
		news[++i] = s[start];
	news[end - start] = '\0';
	return (news);
}
