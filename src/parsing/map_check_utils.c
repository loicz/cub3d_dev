/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:57:56 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 02:53:39 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_valid_char(char c)
{
	return (c == ' ' || c == '1' || c == '0' || is_player_char(c));
}

static char	get_cell(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->height)
		return (' ');
	if (x < 0 || x >= map->row_len[y])
		return (' ');
	return (map->grid[y][x]);
}

static int	is_open(t_map *map, int x, int y)
{
	if (get_cell(map, x + 1, y) == ' ')
		return (1);
	if (get_cell(map, x - 1, y) == ' ')
		return (1);
	if (get_cell(map, x, y + 1) == ' ')
		return (1);
	if (get_cell(map, x, y - 1) == ' ')
		return (1);
	return (0);
}

int	is_map_closed(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->row_len[y])
		{
			if (map->grid[y][x] == '0' && is_open(map, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}
