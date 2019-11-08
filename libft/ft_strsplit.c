/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 07:51:34 by angonyam          #+#    #+#             */
/*   Updated: 2017/07/14 06:55:16 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_add_chars(char const *s, char **new_array, char c)
{
	int i;
	int	letter;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		letter = 0;
		while (s[i] != c && s[i] != '\0')
		{
			new_array[count][letter] = s[i];
			letter++;
			i++;
			if (s[i] == c || s[i] == '\0')
			{
				count++;
				break ;
			}
		}
		if (s[i] == '\0')
			break ;
		i++;
	}
	return (new_array);
}

static char	**ft_alloc_chars(char **array, const char *s, char c)
{
	int i;
	int chars;
	int count;

	chars = 0;
	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i] != '\0')
			{
				i++;
				chars++;
			}
			if (!(array[count] = (char*)ft_strnew(chars)))
				return (NULL);
			count++;
			chars = 0;
		}
		while (s[i] == c)
			i++;
	}
	return ((array = ft_add_chars(s, array, c)));
}

static char	**ft_alloc_arrays(char **array, const char *s, char c)
{
	int i;
	int	slot_1;
	int delim;

	slot_1 = 0;
	i = 0;
	delim = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c && delim)
			slot_1++;
		delim = (s[i] == c);
		i++;
	}
	array = (char **)ft_memalloc(sizeof(char*) * (slot_1 + 1));
	if (array == NULL)
		return (NULL);
	array = ft_alloc_chars(array, s, c);
	return (array);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		i;

	if (!s)
		return (NULL);
	array = NULL;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (ft_alloc_arrays(array, s, c));
		i++;
	}
	if (s[i] == '\0')
		array = (char**)ft_memalloc(sizeof(char *) * 1);
	return (array);
}
