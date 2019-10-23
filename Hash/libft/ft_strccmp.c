/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:57:58 by gsferopo          #+#    #+#             */
/*   Updated: 2017/09/04 08:20:34 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strccmp(char *s1, char *s2)
{
	int		i;
	char	*ls1;
	char	*ls2;

	ls1 = (char *)ft_tolowerstr(s1);
	ls2 = (char *)ft_tolowerstr(s2);
	i = 0;
	while (ls1[i] != '\0' && ls2[i] != '\0' && ls1[i] == ls2[i])
		i++;
	return (ls1[i] - ls2[i]);
}
