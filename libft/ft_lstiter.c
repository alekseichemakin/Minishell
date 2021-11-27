/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 14:03:45 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 14:07:20 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *begin_lst, void (*f)(void *))
{
	while (begin_lst)
	{
		if (f)
			f(begin_lst->content);
		begin_lst = begin_lst->next;
	}
}
