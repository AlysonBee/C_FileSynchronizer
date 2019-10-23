/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 15:56:31 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/06 15:58:12 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*str;
	int		i;

	i = -1;
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	while (++i <= (int)size)
		str[i] = '\0';
	return (str);
}
