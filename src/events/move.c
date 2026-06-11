/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:39:20 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/10 23:13:16 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_walkable(t_game *game, int x, int y)
{
	char	cell;

	if (y < 0 || y >= game->map.height)
		return (1);
	if (x < 0 || x >= game->map.row_len[y])
		return (1);
	cell = game->map.grid[y][x];
	if (cell == '1' || cell == ' ')
		return (1);
	return (0);
}

int	can_stand_at(t_game *game, double x, double y)
{
	int	left;
	int	right;
	int	top;
	int	bottom;

	left = (int)floor(x - PLAYER_RADIUS);
	right = (int)floor(x + PLAYER_RADIUS);
	top = (int)floor(y - PLAYER_RADIUS);
	bottom = (int)floor(y + PLAYER_RADIUS);
	if (is_walkable(game, left, top))
		return (0);
	if (is_walkable(game, right, top))
		return (0);
	if (is_walkable(game, left, bottom))
		return (0);
	if (is_walkable(game, right, bottom))
		return (0);
	return (1);
}

int	move_player(t_game *game, double dx, double dy)
{
	double	new_x;
	double	new_y;
	int		moved;

	moved = 0;
	new_x = game->player.pos.x + dx;
	if (can_stand_at(game, new_x, game->player.pos.y))
	{
		game->player.pos.x = new_x;
		moved = 1;
	}
	new_y = game->player.pos.y + dy;
	if (can_stand_at(game, game->player.pos.x, new_y))
	{
		game->player.pos.y = new_y;
		moved = 1;
	}
	return (moved);
}
