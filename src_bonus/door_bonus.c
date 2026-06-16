/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:37:22 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/16 23:43:41 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	door_open(t_game *game, t_ray ray)
{
	int	ret;

	ret = 1;
	launch_ray((WIN_W - 1) / 2, game, &game->ray);
	if (game->map.grid[game->ray.mapY][game->ray.mapX] == '2')
		game->map.grid[game->ray.mapY][game->ray.mapX] = '3';
	else if (((ray.mapX + 1) < game->map.row_len[ray.mapY]
			&& game->map.grid[ray.mapY][ray.mapX + 1] == '3'))
		game->map.grid[game->ray.mapY][game->ray.mapX + 1] = '2';
	else if (((ray.mapX - 1) >= 0 && game->map.grid[ray.mapY][ray.mapX
			- 1] == '3'))
		game->map.grid[game->ray.mapY][game->ray.mapX - 1] = '2';
	else if (((ray.mapY + 1) < game->map.height && game->map.grid[ray.mapY
			+ 1][ray.mapX] == '3'))
		game->map.grid[game->ray.mapY + 1][game->ray.mapX] = '2';
	else if ((ray.mapY - 1) >= 0 && game->map.grid[ray.mapY
		- 1][ray.mapX] == '3')
		game->map.grid[game->ray.mapY - 1][game->ray.mapX] = '2';
	else
		ret = 0;
	return (ret);
}
