/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 12:27:04 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/10 00:50:32 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_msg(char *s)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

static void	destroy_img(t_mlx *mlx, t_img *img)
{
	if (!mlx || !mlx->ptr || !img || !img->img)
		return ;
	mlx_destroy_image(mlx->ptr, img->img);
	img->img = NULL;
	img->addr = NULL;
}

static void	destroy_textures(t_mlx *mlx)
{
	int	i;

	if (!mlx)
		return ;
	i = 0;
	while (i < 4)
	{
		destroy_img(mlx, &mlx->tex[i]);
		i++;
	}
}

void	destroy_mlx(t_game *game)
{
	t_mlx	*mlx;

	if (!game)
		return ;
	mlx = &game->mlx;
	if (!mlx->ptr)
		return ;
	if (mlx->win)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		mlx->win = NULL;
	}
	destroy_textures(mlx);
	destroy_img(mlx, &mlx->frame);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	mlx->ptr = NULL;
}

int	on_destroy(t_game *game)
{
	mlx_loop_end(game->mlx.ptr);
	return (0);
}
// void	close_window(t_game *game, t_img img)
// {
// 	mlx_destroy_image(img.ptr, img.img);
// 	mlx_destroy_window((img.ptr), img.win);
// 	mlx_loop_end(img.ptr);
// 	mlx_destroy_display(img.ptr);
// 	free(img.ptr);
// }
//
// void	exit_cub3d(t_game *game)
// {
// 	close_window(game, game->frame);
// 	free_parser_data(game);
// 	exit(1);
// }
