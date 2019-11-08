/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 16:11:11 by angonyam          #+#    #+#             */
/*   Updated: 2017/06/09 10:24:03 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static char		*ft_strrev(char *str)
{
	int		i;
	int		limit;
	char	temp;

	limit = ft_strlen(str);
	i = -1;
	while (++i < --limit)
	{
		temp = str[i];
		str[i] = str[limit];
		str[limit] = temp;
	}
	return (str);
}

static char		*ft_creating_space(int n, int neg, int i)
{
	char	*str;
	int		num;

	num = (n * neg);
	while (num != 0)
	{
		if (num < 0)
			num *= -1;
		num /= 10;
		i++;
	}
	if (neg == -1)
		i++;
	str = ft_strnew(--i);
	if (!str)
		return (NULL);
	return (str);
}

static char		*ft_int_max(char *str)
{
	int		i;
	char	*min;

	str = ft_strnew(12);
	if (!str)
		return (NULL);
	i = 0;
	min = "-2147483648";
	while (i < 11)
	{
		str[i] = min[i];
		i++;
	}
	return (str);
}

static char		*ft_loop(int n, char *str, int neg)
{
	int i;

	i = 0;
	while (n != 0)
	{
		str[i] = ((n % 10) + '0');
		n /= 10;
		i++;
	}
	if (neg == -1)
		str[i] = '-';
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		neg;

	i = 0;
	neg = 1;
	if (n < 0)
	{
		n *= -1;
		i = 1;
		neg = -1;
	}
	str = ft_creating_space(n, neg, i);
	if (!str)
		return (NULL);
	if (n == (-2147483647 - 1))
		return (ft_int_max(str));
	else if (n == 0)
	{
		str[i] = '0';
		return (str);
	}
	str = ft_loop(n, str, neg);
	ft_strrev(str);
	return (str);
}
