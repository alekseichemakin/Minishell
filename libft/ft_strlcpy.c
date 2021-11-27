/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 13:19:31 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/16 14:09:00 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	ls;

	ls = 0;
	n = 0;
	if (src && dst)
	{
		ls = ft_strlen(src);
		if (size > 0)
		{
			while (n < size - 1 && n < ls)
			{
				dst[n] = src[n];
				n++;
			}
			dst[n] = '\0';
		}
	}
	return (ls);
}
