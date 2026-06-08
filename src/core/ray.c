/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/08 16:37:24 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

double launch_ray(int nb, t_game *game)
{
	double caméraX;
	double rayDirX;
	double rayDirY;

	caméraX = 2 * nb / (double)WIN_W - 1;
	rayDirX = game->player.dir.x + game->player.plane.x * caméraX;
	rayDirY = game->player.dir.y + game->player.plane.y * caméraX;
	return()
}