/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/09 17:19:58 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calcul_sidedist(t_game *game, t_ray *ray, int mapX, int mapY)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (game->player.pos.x - mapX) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (mapX + 1.0 - game->player.pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (game->player.pos.y - mapY) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (mapY + 1.0 - game->player.pos.y) * ray->deltaDist.y;
	}
}

double launch_ray(int nb, t_game *game, t_ray ray)
{
	double caméraX;
	int side;
	int mapX;
	int mapY;
	double perp_wall_dist;
	
	perp_wall_dist = 0.1;
	mapX = (int)game->player.pos.x;
	mapY = (int)game->player.pos.y;
	caméraX = 2 * nb / (double)WIN_W - 1;
	ray.rayDir.x = game->player.dir.x + game->player.plane.x * caméraX;
	ray.rayDir.y = game->player.dir.y + game->player.plane.y * caméraX;
	ray.deltaDist.x = fabs(1 / ray.rayDir.x);
	ray.deltaDist.y = fabs(1 / ray.rayDir.y);
	calcul_sidedist(game, &ray, mapX, mapY);
	while (1)
	{
		if (ray.sideDist.x < ray.sideDist.y)
		{
			ray.sideDist.x += ray.deltaDist.x;
			mapX += ray.step.x;
			side = 0;
		}
		else
		{
			ray.sideDist.y += ray.deltaDist.y;
			mapY += ray.step.y;
			side = 1;
		}
		if (game->map.grid[mapY][mapX] == '1')
			break;
	}
	if (side == 0)
		perp_wall_dist = (mapX - game->player.pos.x + (1 - (double)ray.step.x) / 2) / ray.rayDir.x;
	else
		perp_wall_dist = (mapY - game->player.pos.y + (1 - (double)ray.step.y) / 2) / ray.rayDir.y;
	return(perp_wall_dist);
}

