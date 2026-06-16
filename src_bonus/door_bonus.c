/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 18:37:22 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/16 18:54:36 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	door_open(t_game *game)
{
	launch_ray((WIN_W - 1) / 2, game, &game->ray);
	if (game->map.grid[game->ray.mapY][game->ray.mapX] == '2')
	{
		game->map.grid[game->ray.mapY][game->ray.mapX] = '3';
		return (1);
	}
	// else if (condition)
	// {
	// 	/* code */
	// }

	return (0);
}