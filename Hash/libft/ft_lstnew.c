/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 14:19:14 by gsferopo          #+#    #+#             */
/*   Updated: 2017/07/31 11:14:28 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp)
	{
		if (content == NULL)
		{
			tmp->content = NULL;
			tmp->content_size = 0;
		}
		else
		{
			tmp->content = (void *)malloc(content_size);
			ft_memcpy(tmp->content, content, content_size);
			tmp->content_size = content_size;
		}
		tmp->next = NULL;
	}
	return (tmp);
}
