/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/13 14:43:01 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

int	color_texture(t_img img, int x, int i, int distance)
{
	int		color;
	double	ratio;
	int		y;

	ratio = (double)i / (double)distance;
	y = ratio * img.height;
	color = img.addr[get_index(x, y, img.line_len)];
	return (color);
}
void	draw_vertical_line(t_game *game, t_vec low, t_vec high, int color)
{
	int	i;
	int	text;
	int	dist;
	int	y;

	if (high.x != low.x)
		return ;
	y = low.y;
	text = 0;
	if (color == -1)
		text = 1;
	i = 0;
	dist = (int)fabs(low.y - high.y);
	while (i <= dist)
	{
		if (text == 1)
			color = color_texture(game->mlx.tex[game->ray.tex], game->ray.texX,
					i, dist);
		if (low.x >= 0 && low.x < game->mlx.frame.width && y >= 0
			&& y < game->mlx.frame.height)
			game->mlx.frame.addr[get_index(low.x, y,
					game->mlx.frame.line_len)] = color;
		y++;
		i++;
	}
}
void	draw_cub(t_game *game, int y, int side, int color)
{
	int		i;
	t_vec	max_win;
	t_vec	min_win;

	min_win.y = y * side / 5;
	max_win.y = (y + 1) * side / 5;
	i = 0;
	while (i < side / 5)
	{
		max_win.x = i + side / 5;
		min_win.x = i + side / 5;
		printf("x:%f\n", min_win.x);
		printf("x:%f\n", min_win.x);
		draw_vertical_line(game, min_win, max_win, color);
		i++;
		// printf("enter\n");
	}
	// printf("\n\n\n\n");
	// printf("side/5:%d\n", side / 5);
	// printf("i:%d\n", i);
}
void	mini_map(t_game *game, int side)
{
	int	X;
	int	startX;
	int	Y;
	int	Ydraw;
	int	Xdraw;
	int	i;

	X = (int)game->player.pos.x - 2;
	Y = (int)game->player.pos.y - 2;
	startX = X;
	while (Y - ((int)game->player.pos.y - 2) < 5)
	{
		X = startX;
		i = 0;
		Ydraw = Y - ((int)game->player.pos.y - 2);
		Xdraw = X - ((int)game->player.pos.x - 2) + 1;
		while (i < 5)
		{
			// if (X == (int)game->player.pos.x && Y == (int)game->player.pos.y)
			// draw_cub(game,Ydraw, side, 0xFF0000);
			if (game->map.grid[Y][X] == '0')
			{
				printf("enter\n");
				printf("Ydraw:%d\n", Ydraw);
				draw_cub(game, Ydraw, Xdraw * side, 0x000000);
			}
			else if (game->map.grid[Y][X] == '1')
				draw_cub(game, Ydraw, Xdraw * side, 0x0010FF);
			i++;
			Xdraw++;
		}
		Y++;
	}
}
void	draw_window(t_game *game, int x, t_vec high_wall, t_vec low_wall)
{
	t_vec	max_win;
	t_vec	min_win;

	max_win.x = x;
	max_win.y = WIN_H;
	min_win.x = x;
	min_win.y = 0;
	if (high_wall.y >= 0 && high_wall.y <= WIN_H / 2)
		draw_vertical_line(game, min_win, high_wall, game->config.ceil_color);
	// dessiner le ciel
	if (low_wall.y <= WIN_H && low_wall.y >= WIN_H / 2)
		draw_vertical_line(game, low_wall, max_win, game->config.floor_color);
	// dessiner le sol
	draw_vertical_line(game, high_wall, low_wall, -1);
	// dessiner le mur
}
