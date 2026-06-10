/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:40:25 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/11 00:45:09 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_forward_move(t_game *game, double *dx, double *dy)
{
	if (game->keys.w)
	{
		*dx += game->player.dir.x;
		*dy += game->player.dir.y;
	}
	if (game->keys.s)
	{
		*dx -= game->player.dir.x;
		*dy -= game->player.dir.y;
	}
}

static void	add_strafe_move(t_game *game, double *dx, double *dy)
{
	double	right_x;
	double	right_y;

	right_x = -game->player.dir.y;
	right_y = game->player.dir.x;
	if (game->keys.d)
	{
		*dx += right_x;
		*dy += right_y;
	}
	if (game->keys.a)
	{
		*dx -= right_x;
		*dy -= right_y;
	}
}

static int	normalize_move(double *dx, double *dy)
{
	double	len;

	len = sqrt((*dx * *dx) + (*dy * *dy));
	if (len == 0)
		return (0);
	*dx = (*dx / len) * MOVE_SPEED;
	*dy = (*dy / len) * MOVE_SPEED;
	return (1);
}

int	update_player(t_game *game)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	add_forward_move(game, &dx, &dy);
	add_strafe_move(game, &dx, &dy);
	if (!normalize_move(&dx, &dy))
		return (0);
	return (move_player(game, dx, dy));
}

int	game_loop(t_game *game)
{
	double	angle;
	int		changed;

	angle = 0;
	changed = 0;
	if (game->keys.left)
		angle -= ROT_SPEED;
	if (game->keys.right)
		angle += ROT_SPEED;
	if (game->keys.mouse_dx)
	{
		angle += game->keys.mouse_dx * MOUSE_SENS;
		game->keys.mouse_dx = 0;
	}
	if (angle != 0)
	{
		rotate_player(&game->player, angle);
		changed = 1;
	}
	if (update_player(game))
		changed = 1;
	if (changed)
		start_engine(game);
	return (0);
}
