/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 09:58:54 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/16 16:07:01 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_len(long nb)
{
	int	len;

	len = 1;
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		sign;
	int		len;
	char	*ptr;

	nb = n;
	sign = (nb < 0);
	if (sign)
		nb = -nb;
	len = cal_len(nb) + sign;
	ptr = ft_calloc(len + 1, 1);
	if (!ptr)
		return (NULL);
	while (len > sign)
	{
		ptr[--len] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign)
		ptr[0] = '-';
	return (ptr);
}
