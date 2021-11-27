/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqueen <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:23:42 by mqueen            #+#    #+#             */
/*   Updated: 2020/11/18 15:37:18 by mqueen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *src)
{
	int	out;
	int	sign;

	out = 0;
	sign = 1;
	while (*src == '\t' || *src == '\n' || *src == '\v' || *src == '\f'
		|| *src == '\r' || *src == ' ')
		src++;
	if (*src == '-')
	{
		sign = -1;
		src++;
	}
	else if (*src == '+')
		src++;
	if (*src >= '0' && *src <= '9')
	{
		while (*src >= '0' && *src <= '9' && *src)
		{
			out = (out * 10) + (*src - '0');
			src++;
		}
		return (sign * out);
	}
	return (0);
}
