/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 10:45:28 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/06 10:48:19 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int i;
	int found;
	int pos;

	pos = 0;
	i = 0;
	found = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	while (big[i] != '\0')
	{
		pos++;
		if (big[i] == little[found++])
			pos--;
		else
		{
			found = 0;
			i = pos;
		}
		if (little[found] == '\0')
			if (found > 0)
				return ((char *)&big[i - found + 1]);
		i++;
	}
	return (NULL);
}
