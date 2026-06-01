/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 01:08:38 by lozhao            #+#    #+#             */
/*   Updated: 2025/11/16 00:32:26 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	**free_all(char **arr, size_t used)
{
	size_t	i;

	i = 0;
	while (i < used)
		free(arr[i++]);
	free(arr);
	return (NULL);
}

static char	**fill_words(char const *s, char c, char **arr, size_t arr_len)
{
	size_t	i;
	size_t	start;
	size_t	count;

	i = 0;
	count = 0;
	while (count < arr_len)
	{
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		arr[count] = ft_substr(s, start, i - start);
		if (!arr[count])
			return (free_all(arr, count));
		count++;
	}
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	size_t	arr_len;
	char	**arr;

	if (!s)
		return (NULL);
	arr_len = count_words(s, c);
	arr = ft_calloc(arr_len + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	return (fill_words(s, c, arr, arr_len));
}
