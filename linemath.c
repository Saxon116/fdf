/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linemath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:12:08 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 11:15:00 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
