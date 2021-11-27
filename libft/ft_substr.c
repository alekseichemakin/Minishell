/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:14:43 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/14 15:19:53 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	l;
	char			*str;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	l = ft_strlen(s);
	if (start >= ft_strlen(s))
	{
		return (ft_strdup("\0"));
	}
	if (l < start + len)
		str = malloc(l - start + 1);
	else
		str = malloc(len + 1);
	if (str == 0)
		return (NULL);
	while (i < len && *s)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
