/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 21:42:41 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/21 01:39:27 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	uc;
	const char		*last;

	if (!s)
		return (NULL);
	last = NULL;
	uc = (unsigned char)c;
	while (*s)
	{
		if ((unsigned char)*s == uc)
			last = s;
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return ((char *)last);
}

//int	main(void)
//{
//	printf("%p\n", ft_strrchr("Heyhey!", 'y'));
//	printf("%p\n", ft_strrchr("Heyhey!", 'e'));
//	printf("%p\n", ft_strrchr("Heyhey!", 't'));
//	printf("%p\n", ft_strrchr("Heyhey!", '\0'));
//}
