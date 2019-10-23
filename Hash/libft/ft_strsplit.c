/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 17:23:30 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/28 08:46:59 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_words(const char *s, char c)
{
	int		i;
	int		d_inc;
	int		counter;

	i = -1;
	d_inc = 0;
	counter = 0;
	while (s[++i] != '\0')
	{
		if (s[i] == c)
			d_inc = 0;
		if (s[i] != c && d_inc == 0)
		{
			counter++;
			d_inc = 1;
		}
	}
	return (counter);
}

static int	getstart(const char *s, char c, int counter, int index)
{
	int start;
	int i;

	i = -1;
	while (s[++i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (counter == index)
			start = i;
		counter++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (start);
}

static char	*get_word(const char *s, char c, int index)
{
	int		i;
	int		counter;
	char	*str;
	int		start;

	start = 0;
	i = -1;
	counter = 0;
	start = getstart(s, c, counter, index);
	i = 0;
	while (s[start + i] != c && s[start + i] != '\0')
		i++;
	str = ft_strnew(i);
	counter = 0;
	while (i--)
	{
		str[counter] = s[start];
		counter++;
		start++;
	}
	return (str);
}

char		**ft_strsplit(char const *s, char c)
{
	int		ti;
	int		index;
	char	**strings;

	index = 0;
	if (s == NULL)
		return (NULL);
	index = check_words(s, c);
	if (index == 0)
	{
		strings = (char **)ft_memalloc(sizeof(char *) * 5);
		if (strings == NULL)
			return (NULL);
		strings[0] = NULL;
		return (strings);
	}
	strings = (char **)ft_memalloc(sizeof(char *) * (index + 1));
	if (strings == NULL)
		return (NULL);
	ti = -1;
	while (++ti < index)
		strings[ti] = get_word(s, c, ti);
	return (strings);
}
