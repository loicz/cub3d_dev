/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:37:22 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/18 11:54:54 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_door_cell(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0 || x >= game->map.row_len[y])
		return (0);
	if (game->map.grid[y][x] == '2')
		return (1);
	if (game->map.grid[y][x] == '3')
		return (1);
	return (0);
}

static int	get_door_target(t_game *game, int *x, int *y)
{
	double	d;
	int		cell_x;
	int		cell_y;

	d = 0.20;
	while (d <= DOOR_RANGE)
	{
		cell_x = (int)floor(game->player.pos.x + game->player.dir.x * d);
		cell_y = (int)floor(game->player.pos.y + game->player.dir.y * d);
		if (is_door_cell(game, cell_x, cell_y))
		{
			*x = cell_x;
			*y = cell_y;
			return (1);
		}
		d += DOOR_STEP;
	}
	return (0);
}

static int	can_close_door(t_game *game, int x, int y)
{
	char	old;
	int		ret;

	old = game->map.grid[y][x];
	game->map.grid[y][x] = '2';
	ret = can_stand_at(game, game->player.pos.x, game->player.pos.y);
	game->map.grid[y][x] = old;
	return (ret);
}

static int	toggle_door_cell(t_game *game, int x, int y)
{
	char	*cell;

	cell = &game->map.grid[y][x];
	if (*cell == '2')
	{
		*cell = '3';
		return (1);
	}
	if (*cell == '3' && can_close_door(game, x, y))
	{
		*cell = '2';
		return (1);
	}
	return (0);
}

int	door_open(t_game *game)
{
	int	x;
	int	y;

	if (!get_door_target(game, &x, &y))
		return (0);
	return (toggle_door_cell(game, x, y));
}
