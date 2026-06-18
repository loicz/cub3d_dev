/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_rotation_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/18 00:55:25 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/18 00:55:44 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_rotation_angle(t_game *game)
{
	double	angle;

	angle = 0;
	if (game->keys.left)
		angle -= ROT_SPEED;
	if (game->keys.right)
		angle += ROT_SPEED;
	if (game->keys.mouse_dx)
	{
		angle += game->keys.mouse_dx * MOUSE_SENS;
		game->keys.mouse_dx = 0;
	}
	return (angle);
}

int	update_rotation(t_game *game)
{
	double	angle;

	angle = get_rotation_angle(game);
	if (angle == 0)
		return (0);
	rotate_player(&game->player, angle);
	return (1);
}
