/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:25:55 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int deal_key(int key, void *param)
{
  t_mlx *mlx;
  double direction;

  direction = 0;
  mlx = (t_mlx *) param;

  if(key == 53 || key == 65307)
      exit(0);
  if(key == 69 || key == 78 || key == 65451 || key == 65453)
  {
    direction = key == 69 || key == 65451  ? .3 : -.3;
    if(mlx->scale + direction >= 0)
      mlx->scale += direction;
		redraw(mlx);
  }

  if(key == 126 || key == 125 || key == 65362 || key == 65364)
  {
    direction = key == 65364 || key == 125 ? 10 : -10;
    mlx->starty += direction;
    redraw(mlx);
  }

  if(key == 123 || key == 124 || key == 65363 || key == 65361)
  {
    direction = key == 65363 || key == 124 ? 10 : -10;
    mlx->startx += direction;
    redraw(mlx);
  }

  if(key == 24 || key == 27 || key == 45 || key == 61)
  {
    direction = key == 24 || key == 61 ? 0.1 : -0.1;
    mlx->amplitude += direction;
    redraw(mlx);
  }

	if(key == 112 || key == 35)
	{
		mlx->projection = !mlx->projection;
		if(mlx->projection)
			mlx->scale = 12;
		else
			mlx->scale = 7;
		redraw(mlx);
	}

  if(key == 8 || key == 114)
  {
    mlx->crazy_rainbow_r = random() / 2 % 255;
    mlx->crazy_rainbow_g = random() / 2 % 255;
    mlx->crazy_rainbow_b = random() / 2 % 255;
    redraw(mlx);
  }
  return (0);
}

int check_fd(int argc, char **argv)
{
	int fd;
	char buf[1];

	if(argc != 2)
	{
		ft_putendl("usage: ./fdf <filename>");
		return (-1);
	}
  fd = open(argv[1], O_RDONLY);
  if(fd < 0 || read(fd, buf , 0) < 0)
  {
    ft_putendl("Not a valid file.");
    return (-1);
  }
	return (fd);
}

void initialize_mlx(t_mlx *mlx)
{
	mlx->list = mlx->head;
  mlx->scale = 9;
  mlx->amplitude = 2;
  mlx->startx = 600;
  mlx->starty = 100;
  mlx->crazy_rainbow_r = 80;
  mlx->crazy_rainbow_g = 4;
  mlx->crazy_rainbow_b = 55;
	mlx->projection = 0;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1200, 700, "Fil de Fer");
  mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1200, 700);
  mlx->img_str =  mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
  &(mlx->size_line), &(mlx->endian));
}

int main(int argc, char **argv)
{
  int        fd;
	t_mlx *mlx;

  fd = check_fd(argc, argv);
	if(fd == -1)
	{
    ft_putendl("Not a valid file.");
    return (0);
  }
  if((mlx = malloc(sizeof(t_mlx))) == NULL)
    return (0);
  mlx->head = get_head(fd);
	if(mlx->head == NULL)
	{
    ft_putendl("Not a valid file.\n");
    return (0);
  }
	initialize_mlx(mlx);
  fill_elements(mlx);
  draw_map(mlx);
  mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
  display_controls(mlx);
  mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
  mlx_loop(mlx->mlx_ptr);
}
