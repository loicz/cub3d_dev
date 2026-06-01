/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 21:43:43 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/16 23:24:47 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//#include <stdio.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*ptr;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	ptr = ft_calloc(len + 1, 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (ptr);
}

//static char	cvert_lo_to_up(unsigned int i, char c)
//{
//	if (i % 2)
//		c -= 32;
//	return (c);
//}
//
//int	main(void)
//{
//	printf("%s", ft_strmapi("abcdefghijk", cvert_lo_to_up));
//	return (0);
//}
