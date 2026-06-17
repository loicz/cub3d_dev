/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/11 11:55:33 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_sidedist(t_game *game, t_ray *ray)
{
	if (ray->rayDir.x < 0)
	{
		ray->step.x = -1;
		ray->sideDist.x = (game->player.pos.x - ray->mapX) * ray->deltaDist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDist.x = (ray->mapX + 1.0 - game->player.pos.x)
			* ray->deltaDist.x;
	}
	if (ray->rayDir.y < 0)
	{
		ray->step.y = -1;
		ray->sideDist.y = (game->player.pos.y - ray->mapY) * ray->deltaDist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDist.y = (ray->mapY + 1.0 - game->player.pos.y)
			* ray->deltaDist.y;
	}
}

int	algorithme_dda(t_game *game, t_ray *ray)
{
	int	side;

	while (1)
	{
		if (ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->mapX += ray->step.x;
			side = 0;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->mapY += ray->step.y;
			side = 1;
		}
		if (ray->mapY < 0 || ray->mapY >= game->map.height)
			return (-1);
		if (ray->mapX < 0 || ray->mapX >= game->map.row_len[ray->mapY])
			return (-1);
		if (game->map.grid[ray->mapY][ray->mapX] == '1'
			|| game->map.grid[ray->mapY][ray->mapX] == '2')
			break ;
	}
	return (side);
}

void	calcul_nb_texture(t_game *game, t_ray *ray)
{
	if (game->map.grid[ray->mapY][ray->mapX] == '2')
		ray->tex = 4;
	else if (ray->side == 0 && ((ray->mapX - 1 >= 0
				&& game->map.grid[ray->mapY][ray->mapX - 1] == '3')
			|| ((ray->mapX + 1) < game->map.row_len[ray->mapY]
				&& game->map.grid[ray->mapY][ray->mapX + 1] == '3')))
		ray->tex = 5;
	else if (ray->side == 1 && ((ray->mapY - 1 >= 0 && game->map.grid[ray->mapY
				- 1][ray->mapX] == '3') || ((ray->mapY + 1) < game->map.height
				&& game->map.grid[ray->mapY + 1][ray->mapX] == '3')))
		ray->tex = 5;
	else if (ray->side == 1 && ray->mapY < game->player.pos.y)
		ray->tex = 0;
	else if (ray->side == 1)
		ray->tex = 1;
	else if (ray->rayDir.x < 0)
		ray->tex = 2;
	else
		ray->tex = 3;
}

void	init_ray(t_game *game, t_ray *ray, int nb)
{
	double	camerax;

	ray->mapX = (int)game->player.pos.x;
	ray->mapY = (int)game->player.pos.y;
	camerax = 2 * nb / (double)WIN_W - 1;
	ray->rayDir.x = game->player.dir.x + game->player.plane.x * camerax;
	ray->rayDir.y = game->player.dir.y + game->player.plane.y * camerax;
	ray->deltaDist.x = fabs(1 / ray->rayDir.x);
	ray->deltaDist.y = fabs(1 / ray->rayDir.y);
}

double	launch_ray(int nb, t_game *game, t_ray *ray)
{
	double	perp_wall_dist;

	init_ray(game, ray, nb);
	calcul_sidedist(game, ray);
	ray->side = algorithme_dda(game, ray);
	if (ray->side == 0)
		perp_wall_dist = (ray->mapX - game->player.pos.x + (1
					- (double)ray->step.x) / 2) / ray->rayDir.x;
	else
		perp_wall_dist = (ray->mapY - game->player.pos.y + (1
					- (double)ray->step.y) / 2) / ray->rayDir.y;
	if (ray->side == 0)
		ray->wallX = game->player.pos.y + perp_wall_dist * ray->rayDir.y;
	else
		ray->wallX = game->player.pos.x + perp_wall_dist * ray->rayDir.x;
	ray->wallX -= floor(ray->wallX);
	ray->texX = (ray->wallX * game->mlx.tex[ray->tex].width);
	calcul_nb_texture(game, ray);
	return (perp_wall_dist);
}
