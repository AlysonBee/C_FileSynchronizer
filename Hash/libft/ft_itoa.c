/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:25:57 by gsferopo          #+#    #+#             */
/*   Updated: 2017/11/15 14:45:56 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int value)
{
	char	*tab;
	char	*s;
	int		len;
	int		n;

	n = value;
	if (n == 0)
		return ("0");
	tab = "0123456789ABCDEF";
	len = ft_numblen(ft_abs(n), 10);
	if (n < 0)
		len++;
	s = (char *)malloc(len + 1);
	s[len] = '\0';
	while (n != 0 && len-- > -1)
	{
		s[len] = tab[ft_abs(n % 10)];
		n /= 10;
	}
	if (len != 0)
		s[0] = '-';
	return (s);
}
