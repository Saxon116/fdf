/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:25:48 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:26:41 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void display_controls(t_mlx *mlx)
{
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 10, 0xFFFFFF, "Zoom: '+' and '-'");
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 30, 0xFFFFFF, "Height: '_' and '='");
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 50, 0xFFFFFF, "Projection: 'p'");
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 70, 0xFFFFFF, "Colors: 'c'");
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 90, 0xFFFFFF, "Move: arrow keys");
  mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 10, 110, 0xFFFFFF, "Quit: Esc");
}

void redraw(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1200, 700);
	mlx->img_str =  mlx_get_data_addr(mlx->img_ptr,
		&(mlx->bpp), &(mlx->size_line), &(mlx->endian));
	draw_map(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
  display_controls(mlx);
}
