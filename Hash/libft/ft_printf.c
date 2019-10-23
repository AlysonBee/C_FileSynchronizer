/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/04 11:09:26 by gsferopo          #+#    #+#             */
/*   Updated: 2017/11/10 11:06:06 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

void	ft_printf(int num, ...)
{
	va_list arg;
	char	*next;

	va_start(arg, num);
	while (num > 0)
	{
		next = va_arg(arg, char *);
		ft_putstr(next);
		num--;
	}
	//ft_putchar('\n');
	va_end(arg);
}
