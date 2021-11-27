/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:47:50 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 14:02:46 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **begin_lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*elem;

	elem = *begin_lst;
	while (elem)
	{
		next = elem->next;
		if (elem)
			del(elem->content);
		free(elem);
		elem = next;
	}
	*begin_lst = NULL;
}
