/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/24 09:48:08 by lvan-gen          #+#    #+#             */
/*   Updated: 2017/09/30 20:10:58 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*skip_space_set_sign(char *str, int *sign)
{
	int		indx;

	indx = 0;
	while (ft_isspace(str[indx]))
		indx++;
	if (str[indx] == '-')
		*sign = -1;
	if (str[indx] == '-' || str[indx] == '+')
		indx++;
	if (!(ft_isdigit(str[indx])))
		return (NULL);
	return (str + indx);
}

static double	min_itoa(char **str)
{
	int		sign;
	double	int_part;

	int_part = 0;
	sign = 1;
	if (**str == '-')
		sign = -1;
	if (**str == '+' || **str == '-')
		(*str)++;
	while (ft_isdigit(**str))
	{
		int_part = int_part * 10 + (**str - '0');
		(*str)++;
	}
	return (int_part * sign);
}

static double	sci_notation(double value, char *str)
{
	int		exp;
	int		indx;
	double	mult;

	exp = (int)min_itoa(&str);
	indx = 0;
	mult = 1;
	while (indx < ft_abs(exp))
	{
		mult *= 10;
		indx++;
	}
	if (exp < 0)
		mult = 1 / mult;
	return (value * mult);
}

double			ft_atof(char *str)
{
	int		sign;
	double	fraction_part;
	double	integer_part;
	int		fraction_div;

	sign = 1;
	fraction_div = 1;
	fraction_part = 0;
	if ((str = skip_space_set_sign(str, &sign)) == NULL)
		return (0);
	integer_part = min_itoa(&str);
	if (*str == '.')
		str++;
	while (ft_isdigit(*str))
	{
		fraction_part = fraction_part * 10 + (*str - '0');
		fraction_div *= 10;
		str++;
	}
	fraction_part /= fraction_div;
	if (*str == 'e' || *str == 'E')
		return (sci_notation(sign * (fraction_part + integer_part), ++str));
	return (sign * (integer_part + fraction_part));
}
