/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 17:29:43 by nkellum           #+#    #+#             */
/*   Updated: 2019/01/17 16:12:23 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

void line(int x1, int y1, int x2, int y2, void *mlx_ptr, void *win_ptr)
{
  float x;
  float direction;

  //printf("line: x1 = %f y1 = %f x2 = %f y2 = %f\n", x1, y1, x2, y2);
  direction = (x2 - x1) < 0 ? -1 : 1;
  x = x1;
  while(x != x2)
  {
    mlx_pixel_put(mlx_ptr, win_ptr, x,
      (y1 + ((y2-y1)*(x-x1))/(x2-x1)), 0x33FF9C);
      x += direction;
  }
}


int deal_key(int key, void *param)
{
  //printf("keycode is %d\n", key);
  if(key == 53)
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

  // printf("Printing file through linked list...\n");
	// while(head)
	// {
  //
	// 	printf("[%s]\n", (char *) head->content);
	// 	index++;
	// 	head = head->next;
	// }
	// printf("Done.\n");

}

void draw_points(t_list *head, int rows, int columns, void *mlx_ptr, void *win_ptr)
{
  int i = 0;
  int j = 0;
  float scale = 10;
  float startX = 500;
  float startY = 100;
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
      // mlx_pixel_put(mlx_ptr, win_ptr, startX + (i * scale * 1.7)
      // - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      // - ft_atoi(elements[i]) * 10, 0x33FF9C);

      line(startX + (i * scale * 1.7)
      - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      - ft_atoi(elements[i]) * 10, startX + ((i + 1) * scale * 1.7)
      - (j * scale * 1.7), startY + ((i + 1) * scale) + (j * scale)
      - ft_atoi(elements[i + 1]) * 10, mlx_ptr, win_ptr);

      line(startX + (i * scale * 1.7)
      - (j * scale * 1.7), startY + (i * scale) + (j * scale)
      - ft_atoi(elements[i]) * 10, startX + (i * scale * 1.7)
      - ((j + 1) * scale * 1.7), startY + (i * scale) + ((j + 1) * scale)
      - ft_atoi(nextelements[i]) * 10, mlx_ptr, win_ptr);

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
  void *mlx_ptr;
  void *win_ptr;
  char *firstline;
  char **array;
  t_list *head;
  float scale = 50;
  int i = 0;

  if(argc != 2)
		return (0);

  fd = open(argv[1], O_RDONLY);
  head = get_head(fd);

  mlx_ptr = mlx_init();
  win_ptr = mlx_new_window(mlx_ptr, 2000, 1000, "it works!");

  //line(316, 499, 310 , 513, mlx_ptr, win_ptr);
  draw_points(head, 10, 10, mlx_ptr, win_ptr);


  //mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0x33FF9C);
  mlx_key_hook(win_ptr, deal_key, (void *)0);

  mlx_loop(mlx_ptr);

}
