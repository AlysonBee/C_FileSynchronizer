/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angonyam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 05:20:45 by angonyam          #+#    #+#             */
/*   Updated: 2017/07/17 13:07:24 by angonyam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*nl;

	nl = (t_list*)malloc(sizeof(t_list));
	if (!nl)
		return (NULL);
	if (!content)
	{
		nl->content = NULL;
		nl->content_size = 0;
	}
	else
	{
		nl->content = ft_memalloc(sizeof(content) * content_size);
		nl->content = ft_memcpy(nl->content, content, content_size);
		nl->content_size = content_size;
	}
	nl->next = NULL;
	return (nl);
}
