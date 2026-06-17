/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:37:22 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/17 15:58:31 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_blocked(t_player play, t_map map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 3)
	{
		x = 0;
		while (x < 3)
		{
			if (map.grid[(int)play.pos.y + (y - 1)][(int)play.pos.x + (x
					- 1)] == '3' && (fabs(play.pos.x
						- (int)play.pos.x) <= PLAYER_RADIUS || fabs(play.pos.y
						- (int)play.pos.y) <= PLAYER_RADIUS))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	door_open(t_game *game, t_ray ray)
{
	int	ret;

	ret = 1;
	launch_ray((WIN_W - 1) / 2, game, &ray);
	if (game->map.grid[ray.mapY][ray.mapX] == '2')
		game->map.grid[ray.mapY][ray.mapX] = '3';
	else if (ray.side == 0 && (ray.mapX + 1) < game->map.row_len[ray.mapY]
		&& game->map.grid[ray.mapY][ray.mapX + 1] == '3'
		&& is_blocked(game->player, game->map))
		game->map.grid[ray.mapY][ray.mapX + 1] = '2';
	else if (ray.side == 0 && (ray.mapX - 1) >= 0
		&& game->map.grid[ray.mapY][ray.mapX - 1] == '3'
		&& is_blocked(game->player, game->map))
		game->map.grid[ray.mapY][ray.mapX - 1] = '2';
	else if (ray.side == 1 && (ray.mapY + 1) < game->map.height
		&& game->map.grid[ray.mapY + 1][ray.mapX] == '3'
		&& is_blocked(game->player, game->map))
		game->map.grid[ray.mapY + 1][ray.mapX] = '2';
	else if (ray.side == 1 && (ray.mapY - 1) >= 0 && game->map.grid[ray.mapY
			- 1][ray.mapX] == '3' && is_blocked(game->player, game->map))
		game->map.grid[ray.mapY - 1][ray.mapX] = '2';
	else
		ret = 0;
	game->ray = ray;
	return (ret);
}
