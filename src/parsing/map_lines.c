/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:56:21 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 01:48:39 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_map_content(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	grow_lines(t_line *tmp)
{
	int		new_cap;
	char	**new_data;
	int		i;

	new_cap = 8;
	if (tmp->capacity)
		new_cap = tmp->capacity * 2;
	new_data = malloc(sizeof(char *) * (new_cap + 1));
	if (!new_data)
		return (1);
	i = 0;
	while (i < tmp->size)
	{
		new_data[i] = tmp->data[i];
		i++;
	}
	new_data[i] = NULL;
	free(tmp->data);
	tmp->data = new_data;
	tmp->capacity = new_cap;
	return (0);
}

int	get_map_content(t_line *tmp, bool map_start, char *line)
{
	if (!map_start)
		return (0);
	if (!has_map_content(line))
		return (1);
	if (tmp->size == tmp->capacity && grow_lines(tmp))
		return (1);
	tmp->data[tmp->size] = ft_strdup(line);
	if (!tmp->data[tmp->size])
		return (1);
	tmp->size++;
	tmp->data[tmp->size] = NULL;
	return (0);
}
