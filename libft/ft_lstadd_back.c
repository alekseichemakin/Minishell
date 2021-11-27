/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:30:26 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 14:32:20 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **begin_lst, t_list *new_item)
{
	t_list	*last;

	last = ft_lstlast(*begin_lst);
	if (last)
		last->next = new_item;
	else
		*begin_lst = new_item;
}
