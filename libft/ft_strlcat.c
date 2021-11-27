/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:50:34 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/05 15:10:02 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	n;
	size_t	i;

	n = 0;
	i = 0;
	while (dst[i] && i < size)
		i++;
	while (src[n] != '\0' && (i + n + 1) < size)
	{
		dst[i + n] = src[n];
		n++;
	}
	if (i < size)
		dst[n + i] = '\0';
	return (i + ft_strlen(src));
}
