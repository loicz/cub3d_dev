/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 14:56:47 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/06 23:59:45 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_dotcub(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len <= 4)
		return (0);
	return (ft_strncmp(path + len - 4, ".cub", 4) == 0);
}

static void	init_parser(t_game *game, t_line *tmp)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->config.tex_path[i] = NULL;
		i++;
	}
	game->config.floor_color = 0;
	game->config.ceil_color = 0;
	game->config.has_floor = 0;
	game->config.has_ceil = 0;
	game->map.grid = NULL;
	game->map.row_len = NULL;
	game->map.height = 0;
	game->map.width = 0;
	tmp->data = NULL;
	tmp->size = 0;
	tmp->capacity = 0;
}

static void	clear_gnl_stash(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
}

static int	parse_fail(char *msg, t_game *game)
{
	free_parser_data(game);
	return (err_msg(msg));
}

int	parse_scene(char *path, t_game *game)
{
	int		fd;
	int		ret;
	t_line	tmp_line;

	init_parser(game, &tmp_line);
	if (!is_dotcub(path))
		return (err_msg("scene file must end with .cub"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (err_msg("cannot open scene file"));
	ret = read_scene(fd, game, &tmp_line);
	if (ret)
		clear_gnl_stash(fd);
	close(fd);
	if (ret)
		return (parse_fail("bad format of .cub file", game));
	return (0);
}
