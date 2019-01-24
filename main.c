/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/24 16:22:43 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

unsigned long createRGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int deal_key(int key, void *param)
{
  //printf("keycode is %d\n", key);
  if(key == 53 || key == 65307)
    exit(0);


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

void draw_points(t_list *head, int width, float ratio, char *img_str)
{
  int i = 0;
  int j = 0;
  float scale = 7;
  t_list *list;
  char **elements;
  char **nextelements;
	int startY = 50;
  list = head;

  ratio = 600;
	printf("didn't segfault yet\n");

  while(list->next)
	{
		elements = ft_strsplit((char *) list->content, ' ');
    nextelements = ft_strsplit((char *) list->next->content, ' ');
    while(elements[i + 1])
    {
      // mlx_pixel_put(mlx_ptr, win_ptr, startX + (i * scale * 1.7)
      // - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      // - ft_atoi(elements[i]) * 10, 0x33FF9C);


      drawLine(ratio + (i * scale * 1.7)
      - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      - ft_atoi(elements[i]) * 10, ratio + ((i + 1) * scale * 1.7)
      - (j * scale * 1.7), startY + ((i + 1) * scale) + (j * scale)
      - ft_atoi(elements[i + 1]) * 10, img_str);

      drawLine(ratio + (i * scale * 1.7)
      - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      - ft_atoi(elements[i]) * 10, ratio + (i * scale * 1.7)
      - ((j + 1) * scale * 1.7), startY + (i * scale) + ((j + 1) * scale)
      - ft_atoi(nextelements[i]) * 10, img_str);

      // OBLIQUE PARALLEL PROJECTION

      // drawLine(ratio + (j * (-scale/2)) + (i * scale),
      // startY + (j * (scale/2))
      // - ft_atoi(elements[i]) * 10, ratio + (j * (-scale/2)) + ((i + 1) * scale)
      // , startY + (j * (scale/2))
      // - ft_atoi(elements[i + 1]) * 10, img_str);
      //
      // drawLine(ratio + (j * - (scale/2)) + (i * scale),
      // startY + (j * (scale/2))
      // - ft_atoi(elements[i]) * 10, ratio + ((j + 1) * - (scale/2)) + (i * scale)
      // , startY + ((j + 1) * (scale/2))
      // - ft_atoi(nextelements[i]) * 10, img_str);

      i++;
    }
    free(elements);
    free(nextelements);
    i = 0;
		j++;
		list = list->next;
	}

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
  float scale = 10;
  int i = 0;
	int width = 1200;
	int height = 700;
	int ratio;
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

  head = get_head(fd);

	// width = num_of_elements(head->content);
	// height = list_length(head);
	// ratio = height;
	// ratio *= 17;

	//printf("width is %d and height is %d ratio is %d\n", width, height, ratio);

	// width = (17 * num_of_elements(head->content)) + (17 * list_length(head));
	// height = width / 1.75;
	printf("didn't segfault yet 1 \n");


  mlx_ptr = mlx_init();
	//mlx->mlx_ptr = mlx_ptr;

	printf("didn't segfault yet 2\n");


	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, width, height, "Fil de Fer");

  mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
  mlx->img_str =  mlx_get_data_addr(mlx->img_ptr, &(bpp), &(size_line), &(endian));

  //line(316, 499, 310 , 513, mlx_ptr, win_ptr);
  draw_points(head, width, ratio, mlx->img_str);

  mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);

  //mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0x33FF9C);
  mlx_key_hook(mlx->win_ptr, deal_key, (void *)0);

  mlx_loop(mlx->mlx_ptr);

}
