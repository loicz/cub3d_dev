/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 00:34:57 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/10 23:14:06 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	k;
	size_t	little_len;

	if (*little == '\0')
		return ((char *)big);
	little_len = ft_strlen(little);
	if (little_len > len)
		return (NULL);
	i = 0;
	while (big[i] && little_len + i <= len)
	{
		k = 0;
		while (k < little_len && big[i + k] == little[k])
			k++;
		if (little[k] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}

//int	main(void)
//{
//	printf("%p\n", ft_strnstr("abcdefghijklmn", "fghij", 10));
//	printf("%p\n", ft_strnstr("abcdefghijklmn", "fghij", 8));
//	printf("%p\n", ft_strnstr("abcdefghijklmn", "fghsj", 10));
//	printf("%p\n", ft_strnstr("abcdefghijklmn", "", 10));
//}
