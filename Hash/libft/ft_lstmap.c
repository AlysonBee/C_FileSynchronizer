/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 13:46:30 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/28 13:51:46 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*tmp;
	t_list	*ph;
	t_list	*pi;

	ph = NULL;
	if ((tmp = (*f)(lst)) == NULL)
		return (NULL);
	ph = tmp;
	pi = ph;
	lst = lst->next;
	while (lst)
	{
		if ((tmp = (*f)(lst)) == NULL)
			return (NULL);
		pi->next = tmp;
		pi = pi->next;
		lst = lst->next;
	}
	return (ph);
}
