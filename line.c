/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:09:46 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/28 16:54:04 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int constrain(int val, int min, int max)
{
	if(val >= max)
		return (max);
	if(val <= min)
		return(min);
	return (val);
}

void fill_pixel(t_mlx *mlx, int x, int y, int amplitude)
{
    int index = 4 * (y * 1200) + 4 * x;
    if(x >= 1200 || x <= 0 || y >= 700 || y <= 0)
      return;
    mlx->img_str[index] =  constrain(mlx->crazy_rainbow_r + amplitude, 0, 255);
    mlx->img_str[index + 1] =  constrain(mlx->crazy_rainbow_g + amplitude * 2, 0, 255);
    mlx->img_str[index + 2] =  constrain(mlx->crazy_rainbow_b + amplitude / 2, 0, 255);
}

void plot(int x, int y, t_mlx *mlx, int amplitude)
{
  fill_pixel(mlx, x, y, amplitude);
}

double ipart(double x)
{
  return floor(x);
}

double round(double x)
{
  return ipart(x + 0.5);
}

double fpart(double x)
{
  return  x - floor(x);
}

double rfpart(double x)
{
  return 1 - fpart(x);
}

void swap(int *x, int *y)
{
  int temp = *x;
  *x = *y;
  *y = temp;
}

void drawLine(int x0 , int y0 , int x1 , int y1, int amplitude, t_mlx *mlx)
{
    int steep = abs(y1 - y0) > abs(x1 - x0) ;

    if (steep)
    {
        swap(&x0 , &y0);
        swap(&x1 , &y1);
    }
    if (x0 > x1)
    {
        swap(&x0 ,&x1);
        swap(&y0 ,&y1);
    }

    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    if (dx == 0.0)
        gradient = 1;

    int xpxl1 = x0;
    int xpxl2 = x1;
    float intersectY = y0;

    if (steep)
    {
        int x;
        for (x = xpxl1 ; x <=xpxl2 ; x++)
        {
            plot(ipart(intersectY), x,  mlx, amplitude);
            plot(ipart(intersectY)-1, x, mlx, amplitude);
            intersectY += gradient;
        }
    }
    else
    {
        int x;
        for (x = xpxl1 ; x <=xpxl2 ; x++)
        {
            plot(x, ipart(intersectY), mlx, amplitude);
            plot(x, ipart(intersectY)-1, mlx, amplitude);
            intersectY += gradient;
        }
    }

}
