/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/05 17:33:34 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// double launch_ray(int nb, )
// {

// }
/* void	draw_segment(t_vec point1, t_vec point2, t_img **img, int step)
{
	int		i;
	float	dx;
	float	dy;
	float	x;
	float	y;

	dx = point2.x - point1.x;
	dy = point2.y - point1.y;
	step = fmax(fabs(dx), fabs(dy));
	dx = dx / step;
	dy = dy / step;
	x = point1.x;
	y = point1.y;
	i = 0;
	while (i <= step)
	{
		if (x >= 0 && x <= (*img)->height && y >= 0 && y <= (*img)->width)
			(*img)->addr[get_index(x, y, (*img)->line_len)] = 0xFFFF25FF;
		x = x + dx;
		y = y + dy;
		i++;
	}
} */
int	get_index(int x, int y, int size_line)
{
	return (y * size_line + x);
}

void	draw_vertical_line(t_vec low, t_vec high, t_img *img, int color)
{
	int i;
	int y;
	int x;

	i = 0;
	y = low.y;
	x = low.x;
	if(high.x != low.x)
		return ;
	while (i <= high.y - low.y)
	{
		if (x >= 0 && x <= img->width && y >= 0 && y <= img->height)
			img->addr[get_index(x, y, img->line_len)] = color;
		y++; 
		i++;
	}
}

void	draw_window(t_game *game, int x, t_vec high_wall, t_vec low_wall)
{
	t_vec max_win;
	t_vec min_win;
	
	max_win.x = x;
	max_win.y = WIN_H;
	min_win.x = x;
	min_win.y = 0;

	// if(high_wall)
	draw_vertical_line(min_win, high_wall, game->frame, game->config.ceil_color); //dessiner le ciel
	draw_vertical_line(low_wall, max_win, game->frame, game->config.floor_color); //dessiner le sol
	draw_vertical_line(high_wall, low_wall, game->frame, 0xFFFF25FF); //dessiner le mur
}

void	start_engine(t_game *game)
{
	int i;
	double dist_ray;
	t_vec high_wall;
	t_vec low_wall;
	i = 0;
	while(i < WIN_W)
	{
		// dist_ray=launch_ray(i, );
		dist_ray = 10;
		high_wall.x = i;
		high_wall.y = WIN_H/2 - ((1/dist_ray * WIN_H) / 2);
		low_wall.x = i;
		low_wall.y = WIN_H/2 + ((1/dist_ray * WIN_H / 2));
		draw_window(game, i, high_wall, low_wall);
		i++;
	}
}
void	initialise_mlx(t_img *img)
{
	img->height = WIN_H;
	img->width = WIN_W;
	img->ptr = mlx_init();
	// printf("ptr: %p\n", img->ptr);
	img->win = mlx_new_window(img->ptr, img->width, img->height, WIN_TITLE);
	// printf("1:win: %p\n", img->win);
	img->img = mlx_new_image(img->ptr, img->width, img->height);
	// printf("1:img: %p\n", img->img);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian );
	img->line_len /= 4;
}
int main (void)
{
	t_game game;
	t_img img;
	
	
	initialise_mlx(&img);
	game.frame = &img;
	game.config.ceil_color = 0xFF0000;
	game.config.floor_color = 0x00ff1a;
	start_engine(&game);
	printf("enter\n");
	mlx_put_image_to_window(game.frame->ptr, game.frame->win, game.frame->img, 0, 0);
	printf("enter\n");
	mlx_loop(img.ptr);
}