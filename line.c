/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 16:09:46 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/25 16:21:27 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void fill_pixel(t_mlx *mlx, int x, int y, int amplitude)
{
    int index = 4 * (y * 1200) + 4 * x;
    int color;
    if(x >= 1200 || x <= 0 || y >= 700 || y <= 0)
    {
      //printf("Trying to draw out of bounds.\n");
      return;
    }
    //printf("x is %d y is %d\n", x % 100, amplitude);
    //printf("amplitude is %d\n", amplitude);
    color = createRGB(mlx->crazy_rainbow_r,
      mlx->crazy_rainbow_g, mlx->crazy_rainbow_b);

    mlx->img_str[index] =  mlx->crazy_rainbow_r;
    mlx->img_str[index + 1] =  mlx->crazy_rainbow_g;
    mlx->img_str[index + 2] =  mlx->crazy_rainbow_b;
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

    // swap the co-ordinates if slope > 1 or we
    // draw backwards
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

    //compute the slope
    float dx = x1-x0;
    float dy = y1-y0;
    float gradient = dy/dx;
    if (dx == 0.0)
        gradient = 1;

    int xpxl1 = x0;
    int xpxl2 = x1;
    float intersectY = y0;

    // main loop
    if (steep)
    {
        int x;
        for (x = xpxl1 ; x <=xpxl2 ; x++)
        {
            // pixel coverage is determined by fractional
            // part of y co-ordinate
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
            // pixel coverage is determined by fractional
            // part of y co-ordinate
            plot(x, ipart(intersectY), mlx, amplitude);
            plot(x, ipart(intersectY)-1, mlx, amplitude);
            intersectY += gradient;
        }
    }

}

// void drawLine(double x0, double y0, double x1, double y1, void *mlx_ptr, void *win_ptr)
// {
//     double dx = 0.0;
//     double dy = 0.0;
//     double gradient = 0.0;
//     double xend = 0.0;
//     double yend = 0.0;
//     double xgap = 0.0;
//     double xpxl1 = 0.0;
//     double xpxl2 = 0.0;
//     double ypxl1 = 0.0;
//     double ypxl2 = 0.0;
//     double intery = 0.0;
//     double x = 0.0;
//     int steep = fabs(y1 - y0) > fabs(x1 - x0);
//
//     if(steep)
//     {
//         swap(&x0, &y0);
//         swap(&x1, &y1);
//     }
//     if(x0 > x1)
//     {
//         swap(&x0, &x1);
//         swap(&y0, &y1);
//     }
//
//     dx = x1 - x0;
//     dy = y1 - y0;
//     gradient = dy / dx;
//     if (dx == 0.0)
//       gradient = 1.0;
//
//     // handle first endpoint
//     xend = round(x0);
//     yend = y0 + gradient * (xend - x0);
//     xgap = rfpart(x0 + 0.5);
//     xpxl1 = xend; // this will be used in the main loop
//     ypxl1 = ipart(yend);
//     if (steep)
//     {
//         plot(ypxl1,   xpxl1, rfpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//         plot(ypxl1+1, xpxl1,  fpart(yend) * xgap* 0xFFFFFF, mlx_ptr, win_ptr);
//     }
//     else
//     {
//         plot(xpxl1, ypxl1  , rfpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//         plot(xpxl1, ypxl1+1,  fpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//     }
//     intery = yend + gradient; // first y-intersection for the main loop
//
//     // handle second endpoint
//     xend = round(x1);
//     yend = y1 + gradient * (xend - x1);
//     xgap = fpart(x1 + 0.5);
//     xpxl2 = xend; //this will be used in the main loop
//     ypxl2 = ipart(yend);
//     if(steep)
//     {
//         plot(ypxl2  , xpxl2, rfpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//         plot(ypxl2+1, xpxl2,  fpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//     }
//     else
//     {
//         plot(xpxl2, ypxl2,  rfpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//         plot(xpxl2, ypxl2+1, fpart(yend) * xgap * 0xFFFFFF, mlx_ptr, win_ptr);
//     }
//
//     // main loop
//     x = xpxl1 + 1;
//     if(steep)
//     {
//            while(x < xpxl2 - 1)
//            {
//                 plot(ipart(intery)  , x, 0xFFFFFF, mlx_ptr, win_ptr);
//                 plot(ipart(intery)+1, x,  0xFFFFFF, mlx_ptr, win_ptr);
//                 intery = intery + gradient;
//                 x++;
//            }
//     }
//     else
//     {
//            while(x < xpxl2 - 1)
//            {
//                 plot(x, ipart(intery),  0xFFFFFF, mlx_ptr, win_ptr);
//                 plot(x, ipart(intery)+1, 0xFFFFFF, mlx_ptr, win_ptr);
//                 intery = intery + gradient;
//                 x++;
//            }
//     }
// }
