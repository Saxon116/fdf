/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:09:46 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 13:00:48 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot(int x, int y, t_mlx *mlx, int amplitude)
{
	int index;

	index = 4 * (y * 1200) + 4 * x;
	mlx->img_str[index] = ft_constrain(mlx->crazy_rainbow_r
		+ amplitude, 0, 255);
	mlx->img_str[index + 1] = ft_constrain(mlx->crazy_rainbow_g
		+ amplitude * 2, 0, 255);
	mlx->img_str[index + 2] = ft_constrain(mlx->crazy_rainbow_b
		+ amplitude / 2, 0, 255);
}

void	lineloop(t_mlx *mlx, int amplitude)
{
	int x;

	x = mlx->xpxl1;
	while (x <= mlx->xpxl2)
	{
		if (mlx->steep)
		{
			plot(ipart(mlx->intersectY), x,  mlx, amplitude);
			plot(ipart(mlx->intersectY) - 1, x, mlx, amplitude);
		}
		else
		{
			plot(x, ipart(mlx->intersectY), mlx, amplitude);
			plot(x, ipart(mlx->intersectY) - 1, mlx, amplitude);
		}
		mlx->intersectY += mlx->gradient;
		x++;
	}
}

int		line_in_window(int x0, int y0, int x1, int y1)
{
	if(x0 >= 1200 || x0 <= 0 || y0 >= 700 || y0 <= 0
	|| x1 >= 1200 || x1 <= 0 || y1 >= 700 || y1 <= 0)
		return (0);
	return (1);
}

void	drawLine(int x0, int y0, int x1, int y1, int amplitude, t_mlx *mlx)
{
		float dx;
		float dy;

		mlx->steep = abs(y1 - y0) > abs(x1 - x0);
		if(!line_in_window(x0, y0, x1, y1))
			return;
    if (mlx->steep)
    {
        swap(&x0 , &y0);
        swap(&x1 , &y1);
    }
    if (x0 > x1)
    {
        swap(&x0 ,&x1);
        swap(&y0 ,&y1);
    }
    dx = x1-x0;
    dy = y1-y0;
    mlx->gradient = dy/dx;
    if (dx == 0.0)
        mlx->gradient = 1;
     mlx->xpxl1 = x0;
     mlx->xpxl2 = x1;
     mlx->intersectY = y0;
		 lineloop(mlx, amplitude);
}
