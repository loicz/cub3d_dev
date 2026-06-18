/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <tle-rhun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:40:25 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/18 00:56:19 by lozhao           ###   ########.fr       */
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

int	game_loop(void *param)
{
	int		changed;
	t_game	*game;

	game = (t_game *)param;
	changed = update_rotation(game);
	if (update_player(game))
		changed = 1;
	if (changed)
		start_engine(game);
	return (0);
}
