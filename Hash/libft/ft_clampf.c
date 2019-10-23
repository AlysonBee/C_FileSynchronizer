/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clampf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 08:16:33 by gsferopo          #+#    #+#             */
/*   Updated: 2017/10/17 14:40:22 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_clampf(double min, double max, double n)
{
	if (n > max)
		return (max);
	if (n < min)
		return (min);
	return (n);
}
