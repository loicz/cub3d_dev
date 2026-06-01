/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 23:30:50 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/21 02:08:39 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (n > 1 && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

//int	main(void)
//{
//	printf("%d\n", ft_strncmp("abcdefg", "abcdefghijk", 7));
//	printf("%d\n", ft_strncmp("abcdefg", "abcdefghijk", 11));
//	printf("%d\n", ft_strncmp("abcdefg", "abcdefohijk", 7));
//	printf("%d\n", ft_strncmp("abcdefg", "abcdefghijk", 0));
//}
