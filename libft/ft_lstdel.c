/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/09 14:02:34 by fsidler           #+#    #+#             */
/*   Updated: 2016/06/22 15:23:07 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*list;
	t_list	*lnext;

	list = *alst;
	while (list)
	{
		lnext = list->next;
		del(list->content, list->content_size);
		free(list);
		list = lnext;
	}
	*alst = NULL;
}
