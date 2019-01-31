/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:31:29 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/31 14:31:00 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "minilibx_macos/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_str;
	t_list		*head;
	float scale;
	float amplitude;
	int crazy_rainbow_r;
	int crazy_rainbow_g;
	int crazy_rainbow_b;
	int startX;
	int startY;
	int projection;
	int bpp;
  int size_line;
  int endian;
	struct s_mlx	*next;
}					t_mlx;

void drawLine(int x0 , int y0 , int x1 , int y1, int amplitude, t_mlx *mlx);

#endif
