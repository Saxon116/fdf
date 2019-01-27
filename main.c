/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/27 18:58:37 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_points(t_list *head, int width, t_mlx *mlx)
{
  int i = 0;
  int j = 0;
  t_list *list;
  char **elements;
  char **nextelements;
  list = head;

  while(list->next)
	{
		elements = ft_strsplit((char *) list->content, ' ');
    nextelements = ft_strsplit((char *) list->next->content, ' ');
    while(elements[i + 1])
    {
      // mlx_pixel_put(mlx_ptr, win_ptr, startX + (i * mlx->scale * 1.7)
      // - (j * mlx->scale * 1.7), mlx->startY + (i * mlx->scale) + (j * mlx->scale)
      // - ft_atoi(elements[i]) * 10, 0x33FF9C);


      // drawLine(mlx->startX + (i * mlx->scale * 1.7)
      // - (j * mlx->scale * 1.7), mlx->startY + (i * mlx->scale) + (j * mlx->scale)
      // - ft_atoi(elements[i]) * mlx->scale * mlx->amplitude, mlx->startX + ((i + 1) * mlx->scale * 1.7)
      // - (j * mlx->scale * 1.7), mlx->startY + ((i + 1) * mlx->scale) + (j * mlx->scale)
      // - ft_atoi(elements[i + 1]) * mlx->scale* mlx->amplitude,
      // ft_atoi(nextelements[i]) * 10, mlx);
			//
      // drawLine(mlx->startX + (i * mlx->scale * 1.7)
      // - (j * mlx->scale * 1.7), mlx->startY + (i * mlx->scale) + (j * mlx->scale)
      // - ft_atoi(elements[i]) * mlx->scale * mlx->amplitude, mlx->startX + (i * mlx->scale * 1.7)
      // - ((j + 1) * mlx->scale * 1.7), mlx->startY + (i * mlx->scale) + ((j + 1) * mlx->scale)
      // - ft_atoi(nextelements[i]) * mlx->scale * mlx->amplitude,
      // ft_atoi(nextelements[i]) * 10, mlx);

      // OBLIQUE PARALLEL PROJECTION

      drawLine(mlx->startX + (j * (-mlx->scale/2)) + (i * mlx->scale),
      mlx->startY + (j * (mlx->scale/2))
      - ft_atoi(elements[i]) * 10, mlx->startX + (j * (-mlx->scale/2)) + ((i + 1) * mlx->scale)
      , mlx->startY + (j * (mlx->scale/2))
      - ft_atoi(elements[i + 1]) * 10, ft_atoi(elements[i + 1]) * 10, mlx);

      drawLine(mlx->startX + (j * - (mlx->scale/2)) + (i * mlx->scale),
      mlx->startY + (j * (mlx->scale/2))
      - ft_atoi(elements[i]) * 10, mlx->startX + ((j + 1) * - (mlx->scale/2)) + (i * mlx->scale)
      , mlx->startY + ((j + 1) * (mlx->scale/2))
      - ft_atoi(nextelements[i]) * 10, ft_atoi(elements[i + 1]) * 10, mlx);

      i++;
    }
    free(elements);
    free(nextelements);
    i = 0;
		j++;
		list = list->next;
	}

}

void redraw(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 1200, 700);
	mlx->img_str =  mlx_get_data_addr(mlx->img_ptr,
		&(mlx->bpp), &(mlx->size_line), &(mlx->endian));
	draw_points(mlx->head, 1200, mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

int deal_key(int key, void *param)
{
  t_mlx *mlx;
  double direction;

	printf("key is %d\n", key);

  direction = 0;
  mlx = (t_mlx *) param;
  if(key == 53 || key == 65307)
    exit(0);
  if(key == 69 || key == 78)
  {
    direction = key == 69 ? 1 : -1;
    mlx->scale += direction;
		redraw(mlx);
  }

  if(key == 126 || key == 125)
  {
    direction = key == 125 ? 10 : -10;
    mlx->startY += direction;
    redraw(mlx);
  }

  if(key == 123 || key == 124)
  {
    direction = key == 124 ? 10 : -10;
    mlx->startX += direction;
    redraw(mlx);
  }

  if(key == 24 || key == 27)
  {
    direction = key == 24 ? 0.1 : -0.1;
    mlx->amplitude += direction;
    redraw(mlx);
  }
  if(key == 15)
  {
    mlx->crazy_rainbow_r = random() % 255;
    mlx->crazy_rainbow_g = random() % 255;
    mlx->crazy_rainbow_b = random() % 255;
    redraw(mlx);
  }
  return (0);
}

int		num_of_elements(char *s)
{
	int words;
	int i;
	int isword;

	i = 0;
	isword = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == ' ')
			isword = 0;
		else if (!isword)
		{
			words++;
			isword = 1;
		}
		i++;
	}
	return (words);
}

int list_length(t_list *head)
{
  t_list *list;
  int length;

  length = 0;
  list = head;
  while(list)
	{
    length++;
    list = list->next;
  }
  return (length);
}

t_list *get_head (int fd)
{
  int index = 0;
	char	*line;
	t_list *head;
	t_list *list;


  get_next_line(fd, &line);
	list = ft_lstnew(line, ft_strlen(line) + 1);
	head = list;


	while (get_next_line(fd, &line))
	{
		list->next = ft_lstnew(line, ft_strlen(line) + 1);
		list = list->next;
	}
  return (head);
}



int main(int argc, char **argv)
{
  int        fd;
	t_mlx *mlx;
  void *mlx_ptr;
  void *win_ptr;
  void *img_ptr;
  char *firstline;
  char **array;
  t_list *head;
  int i = 0;
	int width = 1200;
	int height = 700;
  int bpp;
  int size_line;
  int endian;
  char *img_str;
  char buf[1];



  if(argc != 2)
	{
		printf("usage: ./fdf <filename>\n");
		return (0);
	}
  fd = open(argv[1], O_RDONLY);

  if(fd < 0 || read(fd, buf , 0) < 0)
  {
    printf("Not a valid file.\n");
    return (0);
  }
  if((mlx = malloc(sizeof(t_mlx))) == NULL)
    return (0);

  mlx->head = get_head(fd);
  mlx->scale = 7;
  mlx->amplitude = 1;
  mlx->startX = 600;
  mlx->startY = 100;
  mlx->color = 0xFFFFFF;
  mlx->crazy_rainbow_r = 0;
  mlx->crazy_rainbow_g = 255;
  mlx->crazy_rainbow_b = 0;

	// width = num_of_elements(head->content);
	// height = list_length(head);
	// mlx->startX = height;
	// mlx->startX *= 17;

	//printf("width is %d and height is %d mlx->startX is %d\n", width, height, mlx->startX);

	// width = (17 * num_of_elements(head->content)) + (17 * list_length(head));
	// height = width / 1.75;


  //mlx_ptr = mlx_init();

	mlx->mlx_ptr = mlx_init();

	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, "Fil de Fer");

  mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
  mlx->img_str =  mlx_get_data_addr(mlx->img_ptr, &(mlx->bpp),
  &(mlx->size_line), &(mlx->endian));

  //line(316, 499, 310 , 513, mlx_ptr, win_ptr);
  draw_points(mlx->head, width, mlx);

  mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);

  //mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0x33FF9C);
  mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);

  mlx_loop(mlx->mlx_ptr);

}
