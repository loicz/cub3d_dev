/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 00:48:28 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/08 01:01:27 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}

//int	main(void)
//{
//	printf("%c\n", ft_toupper('f'));
//	printf("%c\n", ft_toupper('K'));
//	printf("%c\n", ft_toupper('9'));
//	printf("%c\n", ft_toupper('1'));
//}
