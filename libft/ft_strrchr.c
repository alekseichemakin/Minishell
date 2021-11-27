/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 12:20:02 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/14 15:14:05 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		len;
	char	*p;

	p = (char *)s;
	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == c)
			return (&p[len]);
		len--;
	}
	return (NULL);
}
