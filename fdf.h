/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:31:29 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:26:17 by nkellum          ###   ########.fr       */
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
t_mapline	*lstnew(char *content, size_t content_size);
void fill_elements(t_mlx *mlx);
t_mapline *get_head (int fd);
void store_line_iso(t_mlx *mlx, int direction, int i, int j);
void store_line_para(t_mlx *mlx, int direction, int i, int j);
void draw_iso(t_mlx *mlx, int i, int j);
void draw_para(t_mlx *mlx, int i, int j);
void draw_map(t_mlx *mlx);
void display_controls(t_mlx *mlx);
void redraw(t_mlx *mlx);

#endif
