/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 19:23:23 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/15 15:13:44 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	size_t			count;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)arr1;
	str2 = (unsigned char *)arr2;
	count = 0;
	while (count < n)
	{
		if (str1[count] == str2[count])
		{
			count++;
		}
		else
			return (str1[count] - str2[count]);
	}
	return (0);
}
