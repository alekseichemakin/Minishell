/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 13:53:57 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/14 17:54:56 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	check(char c, const char *chto)
{
	size_t	i;

	i = 0;
	while (chto[i] != '\0')
	{
		if (chto[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *gde, char const *chto)
{
	char	*str;
	size_t	i;
	size_t	end;
	size_t	start;

	if (!gde || !chto)
		return (NULL);
	i = ft_strlen(gde);
	while (i > 0 && check(gde[i - 1], chto) == 1)
		i--;
	end = i;
	i = 0;
	while (i <= end && check(gde[i], chto) == 1)
		i++;
	start = i;
	i = -1;
	str = malloc(end - start + 1);
	if (!str)
		return (NULL);
	while (start < end)
		str[++i] = gde[start++];
	str[i] = '\0';
	return (str);
}
