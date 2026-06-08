/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 11:32:46 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 00:44:39 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_begin(char c)
{
	return (c == '0' || c == '1' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

static int	is_config_done(t_config *config)
{
	return (config->tex_path[NORTH] && config->tex_path[SOUTH]
		&& config->tex_path[WEST] && config->tex_path[EAST]
		&& config->has_floor && config->has_ceil);
}

int	get_map_config(t_game *game, bool *map_start, char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_config_space(line[i]))
		i++;
	if (*map_start || !line[i])
		return (0);
	if (is_config_id(line + i))
		return (read_config_info(game, line + i));
	if (is_map_begin(line[i]))
	{
		if (!is_config_done(&game->config))
			return (1);
		*map_start = true;
		return (0);
	}
	return (1);
}
