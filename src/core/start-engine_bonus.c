/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start-engine_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:44:12 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/13 12:06:57 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	start_engine(t_game *game)
{
	int		i;
	double	dist_ray;
	t_vec	high_wall;
	t_vec	low_wall;
	int		side;

	if (WIN_W >= WIN_H)
		side = WIN_H / 5;
	else
		side = WIN_W / 5;
	i = 0;
	while (i < WIN_W)
	{
		dist_ray = launch_ray(i, game, &game->ray);
		high_wall.x = i;
		high_wall.y = WIN_H / 2 - ((1 / dist_ray * WIN_H) / 2);
		low_wall.x = i;
		low_wall.y = WIN_H / 2 + ((1 / dist_ray * WIN_H / 2));
		draw_window(game, i, high_wall, low_wall);
		i++;
	}
	if (game->map.height > 5 && game->map.width > 5)
		mini_map(game, side);
	mlx_put_image_to_window(game->mlx.ptr, game->mlx.win, game->mlx.frame.img,
		0, 0);
	// mlx_put_image_to_window(game->mlx.ptr, game->mlx.win,
	// game->mlx.mini_map.img, 0, 0);
}
int	load_texture(t_game *game, t_img *tex, int i)
{
	tex->img = mlx_xpm_file_to_image(game->mlx.ptr, game->config.tex_path[i],
			&game->mlx.tex[i].width, &game->mlx.tex[i].height);
	if (!tex->img)
		return (err_msg("texture load failed, expected a valid XPM file"));
	tex->addr = (int *)mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (err_msg("texture load failed, expected a valid XPM file"));
	tex->line_len /= 4;
	return (0);
}
int	init_mlx(t_game *game)
{
	t_mlx	*mlx;
	int		i;

	i = 0;
	mlx = &game->mlx;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (err_msg("mlx: init failed"));
	mlx->win = mlx_new_window(mlx->ptr, WIN_W, WIN_H, WIN_TITLE);
	if (!mlx->win)
		return (err_msg("mlx: window creation failed"));
	mlx->frame.width = WIN_W;
	mlx->frame.height = WIN_H;
	mlx->frame.img = mlx_new_image(mlx->ptr, WIN_W, WIN_H);
	if (!mlx->frame.img)
		return (err_msg("mlx: image creation failed"));
	mlx->frame.addr = (int *)mlx_get_data_addr(mlx->frame.img, &mlx->frame.bpp,
			&mlx->frame.line_len, &mlx->frame.endian);
	mlx->frame.line_len /= 4;
	while (i < 4)
	{
		load_texture(game, &game->mlx.tex[i], i);
		i++;
	}
	return (0);
}
// void	init_mini_map(t_game *game, t_mlx *mlx)
// {
// 	int	side;

// 	if (WIN_W >= WIN_H)
// 		side = WIN_H / 5;
// 	else
// 		side = WIN_W / 5;
// 	mlx->mini_map.width = side;
// 	mlx->mini_map.height = side;
// 	mlx->mini_map.img = mlx_new_image(mlx->ptr, side, side);
// 	if (!mlx->mini_map.img)
// 		return (err_msg("mlx: image creation failed"));
// 	mlx->mini_map.addr = (int *)mlx_get_data_addr(mlx->mini_map.img,
// 			&mlx->mini_map.bpp, &mlx->mini_map.line_len, &mlx->mini_map.endian);
// 	mlx->mini_map.line_len /= 4;
// }
int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (err_msg("usage: ./cub3D <map.cub>"));
	ft_bzero(&game, sizeof(t_game));
	if (parse_scene(av[1], &game))
		return (1);
	if (init_mlx(&game))
	{
		destroy_mlx(&game);
		free_parser_data(&game);
		return (1);
	}
	// init_mini_map(&game, &game.mlx);
	setup_hooks(&game);
	start_engine(&game);
	mlx_loop(game.mlx.ptr);
	destroy_mlx(&game);
	free_parser_data(&game);
	return (0);
}
