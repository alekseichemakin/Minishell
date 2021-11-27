/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:56 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/16 16:23:32 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *gde, const char *chto, size_t len)
{
	size_t	n;
	size_t	i;

	if (chto[0] == '\0')
		return ((char *)gde);
	i = 0;
	while (i < len && gde[i] != '\0')
	{
		n = 0;
		while (i + n < len && gde[i + n] == chto[n])
		{
			if (chto[n + 1] == '\0')
				return ((char *)(gde + i));
			n++;
		}
		i++;
	}
	return (NULL);
}
