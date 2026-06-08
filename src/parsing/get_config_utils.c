/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_config_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 11:36:15 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/08 01:19:28 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_atoi_rgb(const char *s, int *out)
{
	int	n;
	int	digit;
	int	i;

	n = 0;
	i = 0;
	while (s[i] && is_config_space(s[i]))
		i++;
	if (!(s[i] >= '0' && s[i] <= '9'))
		return (1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		digit = s[i] - '0';
		if (n > (255 - digit) / 10)
			return (1);
		n = n * 10 + digit;
		i++;
	}
	while (s[i] && is_config_space(s[i]))
		i++;
	if (s[i] != '\0')
		return (1);
	*out = n;
	return (0);
}

static int	rgb_to_int(int rgb[3])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

static int	set_color_value(t_game *game, char color_p, int color)
{
	if (color_p == 'F')
	{
		if (game->config.has_floor)
			return (1);
		game->config.floor_color = color;
		game->config.has_floor = 1;
	}
	else if (color_p == 'C')
	{
		if (game->config.has_ceil)
			return (1);
		game->config.ceil_color = color;
		game->config.has_ceil = 1;
	}
	else
		return (1);
	return (0);
}

static int	read_rgb_part(char *line, int *i, int *out)
{
	int	start;

	start = *i;
	while (line[*i] && line[*i] != ',')
		(*i)++;
	if (start == *i)
		return (1);
	if (line[*i] == ',')
	{
		line[(*i)++] = '\0';
		if (!line[*i])
			return (1);
	}
	return (ft_atoi_rgb(line + start, out));
}

int	write_colors(char *line, char color_p, t_game *game)
{
	int	i;
	int	count;
	int	tmp_color;
	int	rgb[3];

	i = 0;
	count = 0;
	while (line[i] && is_config_space(line[i]))
		i++;
	while (line[i])
	{
		if (count == 3 || read_rgb_part(line, &i, &tmp_color))
			return (1);
		rgb[count++] = tmp_color;
		if (!line[i] && count != 3)
			return (1);
	}
	if (count != 3)
		return (1);
	return (set_color_value(game, color_p, rgb_to_int(rgb)));
}
