/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/08 21:02:34 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calcul_sidedist(t_ray *ray, int mapX, int mapY)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (ray->pos.x - mapX) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (mapX + 1.0 - ray->pos.x) * ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (ray->pos.y - mapY) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (mapY + 1.0 - ray->pos.y) * ray->deltaDist.y;
	}
}

double launch_ray(int nb, t_game *game, t_ray ray)
{
	double caméraX;
	// int side;
	int len_ray;
	int mapX;
	int mapY;
	// int perp_wall_dist;
	
	// perp_wall_dist = 1;
	len_ray = 0;
	mapX = game->player.pos.x;
	mapY = game->player.pos.y;
	printf("mapX:%d\n", mapX);
	printf("mapY:%d\n", mapY);
	caméraX = 2 * nb / (double)WIN_W - 1;
	ray.rayDir.x = game->player.dir.x + game->player.plane.x * caméraX;
	ray.rayDir.y = game->player.dir.y + game->player.plane.y * caméraX;
	ray.deltaDist.x = fabs(1 / ray.rayDir.x);
	ray.deltaDist.y = fabs(1 / ray.rayDir.y);
	calcul_sidedist(&ray, mapX, mapY);
	while (1)
	{
		if (ray.sideDist.x < ray.sideDist.y)
		{
			ray.sideDist.x += ray.deltaDist.x;
			mapX += ray.step.x;
			len_ray += ray.sideDist.x;
			// side = 0;
		}
		else
		{
			ray.sideDist.y += ray.deltaDist.y;
			mapY += ray.step.y;
			len_ray += ray.sideDist.y;
			// side = 1;
		}
		if (game->map.grid[mapX][mapY] > 0)
			break;
	}
	// if (side == 0)
	// 	perp_wall_dist = ray.sideDist.x - ray.deltaDist.x;
	// else
	// 	perp_wall_dist = ray.sideDist.y - ray.deltaDist.y;
	return(len_ray);
}

