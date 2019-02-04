/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:13:44 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mapline	*lstnew(char *content, size_t content_size)
{
	t_mapline *t;

	if ((t = malloc(sizeof(t_mapline))) == NULL)
		return (0);
	if (content == NULL)
	{
		t->content = NULL;
		t->content_size = 0;
	}
	else
	{
		if ((t->content = malloc(content_size)) == NULL)
		{
			free(t);
			return (0);
		}
		ft_memcpy(t->content, content, content_size);
		t->content_size = content_size;
	}
	t->next = NULL;
	return (t);
}

void fill_elements(t_mlx *mlx)
{
  t_mapline *list;

  list = mlx->head;

  while(list->next)
	{
    list->elements = ft_strsplit((char *) list->content, ' ');
    list->nextelements = ft_strsplit((char *) list->next->content, ' ');
    list = list->next;
  }
}

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

int deal_key(int key, void *param)
{
  t_mlx *mlx;
  double direction;

	//ft_putendl("key is %d\n", key);
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

t_mapline *get_head (int fd)
{
  int gnl;
	char	*line;
	t_mapline *head;
	t_mapline *list;



  gnl = get_next_line(fd, &line);
	if(!gnl)
		return (NULL);
	list = lstnew(line, ft_strlen(line) + 1);
	head = list;
  free(line);


	while (get_next_line(fd, &line))
	{
		list->next = lstnew(line, ft_strlen(line) + 1);
		list = list->next;
    free(line);
	}
  return (head);
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
