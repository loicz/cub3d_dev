/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/08 11:38:58 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"



void	start_engine(t_game *game)
{
	int		i;
	double	dist_ray;
	t_vec	high_wall;
	t_vec	low_wall;

	i = 0;
	while (i < WIN_W)
	{
		// dist_ray=launch_ray(i, );
		dist_ray = 2;
		high_wall.x = i;
		high_wall.y = WIN_H / 2 - ((1 / dist_ray * WIN_H) / 2);
		low_wall.x = i;
		low_wall.y = WIN_H / 2 + ((1 / dist_ray * WIN_H / 2));
		draw_window(game, i, high_wall, low_wall);
		i++;
	}
}

void	initialise_direction_player(t_game *game, int y, int x)
{
	if(game->map.grid[y][x] == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	if(game->map.grid[y][x] == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	if(game->map.grid[y][x] == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	if(game->map.grid[y][x] == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
}

void	initialise_player(t_game *game)
{
	int y;
	int x;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if(game->map.grid[y][x] != 'N' || game->map.grid[y][x] != 'S'
			|| game->map.grid[y][x] != 'E' || game->map.grid[y][x] != 'W')
			{
				game->player.pos.x = x - 0.5;
				game->player.pos.y = y - 0.5;
				break;
			}
			x++;
		}
		if(game->map.grid[y][x] != '\0')
			break;
		y++;
	}
	initialise_direction_player(game, y, x);
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
	img->addr = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->line_len /= 4;
}
int	main(void)
{
	t_game game;
	t_img img;

	initialise_mlx(&img);
	game.frame = &img;
	game.config.ceil_color = 0xFF0000;
	game.config.floor_color = 0x00ff1a;
	initialise_player(&game);
	start_engine(&game);
	// printf("enter\n");
	mlx_put_image_to_window(game.frame->ptr, game.frame->win, game.frame->img,
		0, 0);
	// printf("enter\n");
	mlx_loop(img.ptr);
}