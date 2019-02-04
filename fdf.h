/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:31:29 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 14:17:37 by nkellum          ###   ########.fr       */
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

typedef struct		s_mapline
{
	char			*content;
	size_t		content_size;
	char 			**elements;
  char 			**nextelements;
	struct s_mapline	*next;
}					t_mapline;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_str;
	t_mapline		*head;
	t_mapline		*list;
	float scale;
	float amplitude;
	float gradient;
	float intersecty;
	int x0;
	int y0;
	int x1;
	int y1;
	int steep;
	int xpxl1;
	int xpxl2;
	int crazy_rainbow_r;
	int crazy_rainbow_g;
	int crazy_rainbow_b;
	int startx;
	int starty;
	int projection;
	int bpp;
  int size_line;
  int endian;
	struct s_mlx	*next;
}					t_mlx;

void drawline(t_mlx *mlx, int amplitude);
double ipart(double x);
double round(double x);
double fpart(double x);
double rfpart(double x);
void swap(int *x, int *y);

#endif
