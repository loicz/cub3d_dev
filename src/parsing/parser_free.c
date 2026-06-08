/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 18:01:16 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 02:55:47 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tmp_lines(t_line *tmp)
{
	int	i;

	if (!tmp || !tmp->data)
		return ;
	i = 0;
	while (i < tmp->size)
	{
		free(tmp->data[i]);
		i++;
	}
	free(tmp->data);
	tmp->data = NULL;
	tmp->size = 0;
	tmp->capacity = 0;
}

static void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(config->tex_path[i]);
		config->tex_path[i] = NULL;
		i++;
	}
	config->has_floor = 0;
	config->has_ceil = 0;
}

static void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->grid)
	{
		while (map->grid[i])
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map->row_len);
	map->grid = NULL;
	map->row_len = NULL;
	map->height = 0;
	map->width = 0;
}

void	free_parser_data(t_game *game)
{
	free_config(&game->config);
	free_map(&game->map);
}
