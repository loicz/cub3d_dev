/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 21:23:25 by lozhao            #+#    #+#             */
/*   Updated: 2026/02/01 22:19:04 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*p = s;

	if (!s)
		return (0);
	while (*p)
		p++;
	return (p - s);
}

int	check_n(const char *stash)
{
	if (!stash)
		return (0);
	while (*stash)
	{
		if (*stash == '\n')
			return (1);
		stash++;
	}
	return (0);
}

char	*gnl_strjoin(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!buffer)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		*stash = '\0';
	}
	new = malloc(ft_strlen(stash) + ft_strlen(buffer) + 1);
	if (!new)
		return (free(stash), NULL);
	i = -1;
	while (stash[++i])
		new[i] = stash[i];
	j = 0;
	while (buffer[j])
		new[i++] = buffer[j++];
	new[i] = '\0';
	return (free(stash), new);
}
