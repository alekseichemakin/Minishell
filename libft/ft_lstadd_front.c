/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 12:49:13 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 13:12:09 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **begin_lst, t_list *new_item)
{
	if (new_item && begin_lst)
	{
		new_item->next = *begin_lst;
		*begin_lst = new_item;
	}
}
