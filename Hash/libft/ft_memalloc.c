/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/07 13:39:39 by gsferopo          #+#    #+#             */
/*   Updated: 2017/06/09 17:12:06 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	char	*memalloc;

	memalloc = malloc(size);
	if (memalloc == NULL)
		return (NULL);
	else
	{
		ft_bzero(memalloc, size);
		return (memalloc);
	}
}
