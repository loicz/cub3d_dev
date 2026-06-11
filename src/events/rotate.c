/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lozhao <lozhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:38:36 by lozhao            #+#    #+#             */
/*   Updated: 2026/06/10 23:32:46 by lozhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	rotate_vec(t_vec *vec, double angle)
{
	double	old_x;
	double	cos_a;
	double	sin_a;

	old_x = vec->x;
	cos_a = cos(angle);
	sin_a = sin(angle);
	vec->x = vec->x * cos_a - vec->y * sin_a;
	vec->y = old_x * sin_a + vec->y * cos_a;
}

void	rotate_player(t_player *player, double angle)
{
	rotate_vec(&player->dir, angle);
	rotate_vec(&player->plane, angle);
}
