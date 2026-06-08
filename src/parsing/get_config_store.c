/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 17:44:29 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 00:51:45 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_config_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

int	is_config_id(char *line)
{
	if (!ft_strncmp(line, "NO", 2) && is_config_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "SO", 2) && is_config_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "WE", 2) && is_config_space(line[2]))
		return (1);
	if (!ft_strncmp(line, "EA", 2) && is_config_space(line[2]))
		return (1);
	if (line[0] == 'F' && is_config_space(line[1]))
		return (1);
	if (line[0] == 'C' && is_config_space(line[1]))
		return (1);
	return (0);
}

static int	get_single_info(char *line, int *start)
{
	int	i;

	i = 0;
	while (line[i] && is_config_space(line[i]))
		i++;
	if (!line[i])
		return (1);
	*start = i;
	while (line[i] && !is_config_space(line[i]))
		i++;
	while (line[i] && is_config_space(line[i]))
		i++;
	if (line[i])
		return (1);
	return (0);
}

static int	set_texture(t_game *game, t_dir dir, char *line)
{
	int	start;

	if (game->config.tex_path[dir])
		return (1);
	if (get_single_info(line, &start))
		return (1);
	game->config.tex_path[dir] = ft_strdup(line + start);
	if (!game->config.tex_path[dir])
		return (1);
	return (0);
}

int	read_config_info(t_game *game, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (set_texture(game, NORTH, line + 2));
	if (!ft_strncmp(line, "SO", 2))
		return (set_texture(game, SOUTH, line + 2));
	if (!ft_strncmp(line, "WE", 2))
		return (set_texture(game, WEST, line + 2));
	if (!ft_strncmp(line, "EA", 2))
		return (set_texture(game, EAST, line + 2));
	if (line[0] == 'F')
		return (write_colors(line + 1, 'F', game));
	if (line[0] == 'C')
		return (write_colors(line + 1, 'C', game));
	return (1);
}
