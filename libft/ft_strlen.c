/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:36:33 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/09 02:01:26 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

//int	main(void)
//{
//	printf("%zu\n", ft_strlen("Heyhey!"));
//	printf("%zu\n", ft_strlen("Hey!"));
//	printf("%zu\n", ft_strlen("89!"));
//	printf("%zu\n", ft_strlen("---"));
//}
