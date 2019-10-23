/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 11:47:37 by gsferopo          #+#    #+#             */
/*   Updated: 2017/11/13 13:39:05 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_list(void *list)
{
	t_lst	*lst;
	t_lst	*tmp;

	lst = (t_lst *)list;
	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}