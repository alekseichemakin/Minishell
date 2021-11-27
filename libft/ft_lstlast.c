/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 13:20:58 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 13:28:33 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst_begin)
{
	while (lst_begin && lst_begin->next)
	{
		lst_begin = lst_begin->next;
	}
	return (lst_begin);
}
