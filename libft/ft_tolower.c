/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:06:07 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/08 10:19:29 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

//int	main(void)
//{
//	printf("%c\n", ft_tolower('H'));
//	printf("%c\n", ft_tolower('s'));
//	printf("%c\n", ft_tolower('9'));
//	printf("%c\n", ft_tolower('P'));
//}
