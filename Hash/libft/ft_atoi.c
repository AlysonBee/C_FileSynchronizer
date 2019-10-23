/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 10:39:48 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/17 14:58:33 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		min(int number, int i, int is_neg)
{
	if (i > 19 && is_neg)
		return (0);
	if (i > 19)
		return (-1);
	if (is_neg)
		return (-number);
	else
		return (number);
}

static int		convnum(char *str, int i, int is_neg)
{
	int	number;
	int j;

	number = 0;
	j = i;
	while ((str[i] >= 48) && (str[i] <= 57))
	{
		if (str[i] != '0')
			j++;
		number *= 10;
		number += ((int)str[i] - 48);
		i++;
	}
	return (min(number, j, is_neg));
}

int				ft_atoi(char *str)
{
	int			i;
	int			is_neg;

	i = 0;
	is_neg = 0;
	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n')
			|| (str[i] == '\v') || (str[i] == '\f') || (str[i] == '\r'))
		i++;
	if (str[i] == 45)
		is_neg = 1;
	if ((str[i] == 45) || (str[i] == 43))
		i++;
	return (convnum(str, i, is_neg));
}
