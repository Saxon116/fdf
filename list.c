/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 15:18:11 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 15:19:53 by nkellum          ###   ########.fr       */
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
