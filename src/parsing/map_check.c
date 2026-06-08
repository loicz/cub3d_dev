/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:59:51 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 02:15:12 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_dir(t_player *player, char c)
{
	player->dir.x = 0;
	player->dir.y = 0;
	player->plane.x = 0;
	player->plane.y = 0;
	if (c == 'N')
		player->dir.y = -1;
	else if (c == 'S')
		player->dir.y = 1;
	else if (c == 'E')
		player->dir.x = 1;
	else
		player->dir.x = -1;
	player->plane.x = -player->dir.y * PLANE_LEN;
	player->plane.y = player->dir.x * PLANE_LEN;
}

static int	set_player(t_game *game, int x, int y, int *players)
{
	char	c;

	if (*players)
		return (1);
	c = game->map.grid[y][x];
	game->player.pos.x = (double)x + 0.5;
	game->player.pos.y = (double)y + 0.5;
	set_player_dir(&game->player, c);
	game->map.grid[y][x] = '0';
	(*players)++;
	return (0);
}

static int	handle_cell(t_game *game, int x, int y, int *players)
{
	char	c;

	c = game->map.grid[y][x];
	if (!is_valid_char(c))
		return (1);
	if (is_player_char(c))
		return (set_player(game, x, y, players));
	return (0);
}

static int	scan_map(t_game *game, int *players)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.row_len[y])
		{
			if (handle_cell(game, x, y, players))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_map(t_game *game)
{
	int	players;

	players = 0;
	if (scan_map(game, &players))
		return (1);
	if (players != 1)
		return (1);
	if (!is_map_closed(&game->map))
		return (1);
	return (0);
}
