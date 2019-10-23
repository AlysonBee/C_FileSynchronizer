/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wrap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 12:59:58 by gsferopo          #+#    #+#             */
/*   Updated: 2018/01/25 15:02:31 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double			ft_wrap(double min, double max, double n)
{
	double		b;

	if (n == 0)
		return (min);
	if (min > max)
	{
		b = min;
		min = max;
		max = b;
	}
	b = 1;
	while (b)
	{
		if (n > max)
			n = min + (n - max - 1);
		else if (n < min)
			n = max - (n + min + 1);
		else
			b = 0;
	}
	return (n);
}
