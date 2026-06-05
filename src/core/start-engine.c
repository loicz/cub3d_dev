/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/04 17:36:22 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
/* 
double launch_ray(int nb, )
{

}
void	draw_segment(t_vec point1, t_vec point2, t_img **img, int step)
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

void	draw_vertical_line(t_vec high, t_vec low, t_img *img)
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
		y += i; 
		if (x >= 0 && x <= img->width && y >= 0 && y <= img->height)
			img->addr[get_index(x, y, img->line_len)] = 0xFFFF25FF;
		i++;
	}
}
/* draw_window(t_game *game, int i, t_vec high, t_vec low)
{
	while(i < WIN_W)
	{

		draw_segment(, game->frame,1);
		i++;
	}
}
start_engine(t_game *game)
{
	int i;
	double dist_ray;
	
	i = 0;
	while(i < WIN_W * PLANE_LEN)
	{
		dist_ray=launch_ray(i, );
		draw_window
		i++;
	}
	
} */
void	initialise_mlx(t_img *img)
{
	img->height = WIN_H;
	img->width = WIN_W;
	img->ptr = mlx_init();
printf("ptr: %p\n", img->ptr);
img->win = mlx_new_window(img->ptr, img->width, img->height, WIN_TITLE);
printf("win: %p\n", img->win);
img->img = mlx_new_image(img->ptr, img->width, img->height);
printf("img: %p\n", img->img);
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian );
	img->line_len /= 4;
}
int main (void)
{
	// t_game game;
	t_img img;
	
	t_vec high;
	t_vec low;
	
	low.x= 56;
	high.x= low.x;
	high.y = 700;
	low.y = 200;
	initialise_mlx(&img);
	// game.frame = img;
	// start_engine(&game);
	draw_vertical_line(high, low, &img);
	mlx_put_image_to_window(img.ptr, img.win, img.img, 0, 0);
	mlx_loop(img.ptr);
}