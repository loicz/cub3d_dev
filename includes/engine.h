/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:07:17 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/06/13 15:29:45 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RAY
double	launch_ray(int nb, t_game *game, t_ray *ray);
// DRAW
void	mini_map(t_game *game, t_minimap mini_mapm, t_player play);
int		get_index(int x, int y, int size_line);
void	draw_vertical_line(t_game *game, t_vec low, t_vec high, int color);
// void	draw_vertical_line(t_vec low, t_vec high, t_img img, int color);
void	draw_window(t_game *game, int x, t_vec high_wall, t_vec low_wall);
