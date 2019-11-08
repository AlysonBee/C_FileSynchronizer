/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 12:54:25 by angonyam          #+#    #+#             */
/*   Updated: 2017/06/20 19:05:16 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *marker;
	t_list *begin;

	begin = f(lst);
	lst = lst->next;
	new = begin;
	while (lst)
	{
		marker = new;
		new = f(lst);
		if (!new)
			return (NULL);
		marker->next = new;
	}
	new->next = NULL;
	return (begin);
}
