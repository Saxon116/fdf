/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:21:35 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:22:22 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void store_line_iso(t_mlx *mlx, int direction, int i, int j)
{
	if(!direction)
	{
		mlx->x0 = mlx->startx + (i * mlx->scale * 1.7)
		- (j * mlx->scale * 1.7);
		mlx->y0 = mlx->starty + (i * mlx->scale) + (j * mlx->scale)
		- ft_atoi(mlx->list->elements[i]) * mlx->scale * mlx->amplitude;
		mlx->x1 = mlx->startx + ((i + 1) * mlx->scale * 1.7)
		- (j * mlx->scale * 1.7);
		mlx->y1 = mlx->starty + ((i + 1) * mlx->scale) + (j * mlx->scale)
		- ft_atoi(mlx->list->elements[i + 1]) * mlx->scale * mlx->amplitude;
	}
	else
	{
		mlx->x0 = mlx->startx + (i * mlx->scale * 1.7)
		- (j * mlx->scale * 1.7);
		mlx->y0 = mlx->starty + (i * mlx->scale) + (j * mlx->scale)
		- ft_atoi(mlx->list->elements[i]) * mlx->scale * mlx->amplitude;
		mlx->x1 = mlx->startx + (i * mlx->scale * 1.7)
		- ((j + 1) * mlx->scale * 1.7);
		mlx->y1 = mlx->starty + (i * mlx->scale) + ((j + 1) * mlx->scale)
		- ft_atoi(mlx->list->nextelements[i]) * mlx->scale * mlx->amplitude;
	}
}

void store_line_para(t_mlx *mlx, int direction, int i, int j)
{
	if(!direction)
	{
		mlx->x0 = mlx->startx + (j * (-mlx->scale/2)) + (i * mlx->scale);
		mlx->y0 = mlx->starty + (j * (mlx->scale/2))
		- ft_atoi(mlx->list->elements[i]) * mlx->scale * mlx->amplitude;
		mlx->x1 = mlx->startx + (j * (-mlx->scale/2)) + ((i + 1) * mlx->scale);
		mlx->y1 = mlx->starty + (j * (mlx->scale/2))
		- ft_atoi(mlx->list->elements[i + 1]) * mlx->scale * mlx->amplitude;
	}
	else
	{
		mlx->x0 = mlx->startx + (j * - (mlx->scale/2)) + (i * mlx->scale);
		mlx->y0 = mlx->starty + (j * (mlx->scale/2))
		- ft_atoi(mlx->list->elements[i]) * mlx->scale * mlx->amplitude;
		mlx->x1 = mlx->startx + ((j + 1) * - (mlx->scale/2)) + (i * mlx->scale);
		mlx->y1 = mlx->starty + ((j + 1) * (mlx->scale/2))
		- ft_atoi(mlx->list->nextelements[i]) * mlx->scale * mlx->amplitude;
	}
}

void draw_iso(t_mlx *mlx, int i, int j)
{
	store_line_iso(mlx, 0, i, j);
	drawline(mlx, ft_max(ft_atoi(mlx->list->elements[i]),
	ft_atoi(mlx->list->elements[i+1])) * mlx->amplitude * 10);
	store_line_iso(mlx, 1, i, j);
	drawline(mlx, ft_max(ft_atoi(mlx->list->elements[i]),
	ft_atoi(mlx->list->nextelements[i])) * mlx->amplitude * 10);
}

// OBLIQUE PARALLEL PROJECTION
void draw_para(t_mlx *mlx, int i, int j)
{
	store_line_para(mlx, 0, i, j);
	drawline(mlx, ft_max(ft_atoi(mlx->list->elements[i]),
	ft_atoi(mlx->list->elements[i+1])) * mlx->amplitude * 10);
	store_line_para(mlx, 1, i, j);
	drawline(mlx, ft_max(ft_atoi(mlx->list->elements[i]),
	ft_atoi(mlx->list->nextelements[i])) * mlx->amplitude * 10);
}

void draw_map(t_mlx *mlx)
{
  int i = 0;
  int j = 0;

  while(mlx->list->next)
	{
    while(mlx->list->nextelements[i] && mlx->list->nextelements[i + 1]
			&& mlx->list->elements[i] && mlx->list->elements[i + 1])
    {
			if(!mlx->projection)
				draw_iso(mlx, i, j);
			else
				draw_para(mlx, i, j);
      i++;
    }
    i = 0;
		j++;
		mlx->list = mlx->list->next;
	}
	mlx->list = mlx->head;
}
