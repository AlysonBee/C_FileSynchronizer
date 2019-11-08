/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/24 10:56:08 by angonyam          #+#    #+#             */
/*   Updated: 2017/07/14 06:46:07 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	*ft_memalloc(size_t size)
{
	void *str;

	if ((int)size < 0)
	{
		return (NULL);
	}
	else
	{
		str = malloc(size);
		if (str)
			ft_bzero(str, size);
		return (str);
	}
}
