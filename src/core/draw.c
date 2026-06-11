/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 17:53:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/11 15:29:57 by tle-rhun         ###   ########.fr       */
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
	// printf("x%d\n", x);
	// printf("distance%d\n", distance);
	// printf("ratio%f\n", ratio);
	y = ratio * img.height;
	// printf("y%d\n", y);
	// printf("x:%d\n", x);
	// printf("img.width:%d\n", img.width);
	color = img.addr[get_index(x % img.width, y, img.line_len)];
	// % img.width);
	// if (x == 0)
	// printf("index0:%d\n", get_index(x, y, img.line_len));
	// printf("color%d\n", color);
	return (color);
}
void	draw_vertical_line(t_game *game, t_vec low, t_vec high, int color)
{
	int	i;
	int	text;
	int	distance;
	int	y;

	if (high.x != low.x)
		return ;
	y = low.y;
	text = 0;
	if (color == -1)
		text = 1;
	i = 0;
	distance = (int)fabs(low.y - high.y);
	while (i <= distance)
	{
		if (text == 1)
			color = color_texture(game->mlx.tex[game->ray.tex], low.x, i,
					distance);
		if (low.x >= 0 && low.x < game->mlx.frame.width && y >= 0
			&& y < game->mlx.frame.height)
			game->mlx.frame.addr[get_index(low.x, y,
					game->mlx.frame.line_len)] = color;
		y++;
		i++;
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
