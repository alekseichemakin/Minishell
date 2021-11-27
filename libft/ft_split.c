/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:08:01 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/17 14:12:00 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	len1(char *str, char c)
{
	size_t	m;
	size_t	i;

	i = 0;
	m = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || str[i + 1] == '\0'))
			m++;
		i++;
	}
	return (m);
}

static	size_t	len2(char *s, char c, size_t i)
{
	size_t	ms;

	ms = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		ms++;
		i++;
	}
	return (ms);
}

static	char	**free_arr(char **arr, size_t a)
{
	while (a >= 0)
		free(arr[a--]);
	free(arr);
	return (NULL);
}

static	char	**get_arr(char **arr, char *s, char c)
{
	size_t	a;
	size_t	b;
	size_t	i;

	a = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			b = 0;
			arr[a] = (char *)malloc(len2(s, c, i) + 1);
			if (!arr[a])
				return (free_arr(arr, a));
			while (s[i] != c && s[i] != '\0')
				arr[a][b++] = s[i++];
			arr[a][b] = '\0';
			a++;
		}
		if (s[i] != '\0')
			i++;
	}
	arr[a] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;

	if (!s)
		return (NULL);
	arr = malloc(sizeof(char *) * (len1((char *)s, c) + 1));
	if (!arr)
		return (NULL);
	arr = get_arr(arr, (char *)s, c);
	return (arr);
}
