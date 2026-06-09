/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/09 11:48:03 by tle-rhun         ###   ########.fr       */
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
		dist_ray=launch_ray(i, game, game->ray);
		high_wall.x = i;
		high_wall.y = WIN_H / 2 - ((1 / dist_ray * WIN_H) / 2);
		low_wall.x = i;
		low_wall.y = WIN_H / 2 + ((1 / dist_ray * WIN_H / 2));
		draw_window(game, i, high_wall, low_wall);
		i++;
	}
	mlx_put_image_to_window(game->frame.ptr, game->frame.win, game->frame.img,
	0, 0);
}

void	initialise_direction_player(t_game *game, int y, int x)
{
	if(game->map.grid[y][x] == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
	}
	else if(game->map.grid[y][x] == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
	}
	else if(game->map.grid[y][x] == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
	}
	else if(game->map.grid[y][x] == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
	}
}
void	initialise_plane_player(t_game *game, int y, int x)
{
	if(game->map.grid[y][x] == 'N')
	{
		game->player.plane.x =  1 * PLANE_LEN;
		game->player.plane.y = 0;
	}
	else if(game->map.grid[y][x] == 'S')
	{
		game->player.plane.x = -1 * PLANE_LEN;
		game->player.plane.y = 0;
	}
	else if(game->map.grid[y][x] == 'E')
	{
		game->player.plane.x = 0;
		game->player.plane.y = 1 * PLANE_LEN;
	}
	else if(game->map.grid[y][x] == 'W')
	{
		game->player.plane.x = 0;
		game->player.plane.y = -1 * PLANE_LEN;
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
			if(game->map.grid[y][x] == 'N' || game->map.grid[y][x] == 'S'
			|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'W')
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
	initialise_plane_player(game, y, x);
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

void initialise_all(t_game *game)
{
	initialise_mlx(&game->frame);
	// initialise_player(game);
	game->config.ceil_color = 0xFF0000;
	game->config.floor_color = 0x00ff1a;
}

int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
	{free_parser_data(&game);
		write(2, "Usage: ./parser_test <map.cub>\n", 31);
		return (1);
	}
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(av[1], &game))
		return (1);
	initialise_all(&game);
	start_engine(&game);

	mlx_loop(game.frame.ptr);
	// free_parser_data(&game);
	return (0);
}
