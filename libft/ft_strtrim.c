/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 16:56:28 by angonyam          #+#    #+#             */
/*   Updated: 2017/06/09 11:34:55 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_check_reverse(char const *s)
{
	int len;
	int i;

	i = 0;
	len = ft_strlen(s);
	len = len - 1;
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
	{
		len--;
		i++;
	}
	return (i);
}

static int		ft_check_front(char const *s)
{
	int i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	int		size;
	int		i;
	int		max;
	char	*str;
	int		j;

	size = ft_strlen(s);
	i = 0;
	max = 0;
	if (s[0] == ' ' || s[0] == '\n' || s[i] == '\t')
		i = ft_check_front(s);
	if (s[size - 1] == ' ' || s[size - 1] == '\n' || s[size - 1] == '\t')
		max = ft_check_reverse(s);
	size = (size - max - i);
	if (size < 0)
		return (ft_strnew(0));
	str = (char*)ft_strnew(size);
	if (str == NULL)
		return (NULL);
	j = 0;
	ft_bzero(str, size);
	while (j < size)
		str[j++] = s[i++];
	str[j++] = '\0';
	return (str);
}
