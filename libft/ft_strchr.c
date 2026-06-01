/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:21:36 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/21 01:56:41 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	k;

	if (!s)
		return (NULL);
	i = 0;
	k = (unsigned char)c;
	while (s[i])
	{
		if (k == (unsigned char)s[i])
			return ((char *)(s + i));
		i++;
	}
	if (k == '\0')
		return ((char *)(s + i));
	return (NULL);
}

//int	main(void)
//{
//	printf("%p\n", (void *)ft_strchr("heyhey!", 'e'));
//	printf("%p\n", (void *)ft_strchr("heyhey!", 'y'));
//	printf("%p\n", (void *)ft_strchr("", 'e'));
//	printf("%p\n", (void *)ft_strchr("heyhey!", '\0'));
//}
