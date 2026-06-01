/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 09:23:01 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/12 11:21:18 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	cpylen;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	cpylen = slen - start;
	if (cpylen > len)
		cpylen = len;
	sub = malloc(cpylen + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, cpylen + 1);
	return (sub);
}
