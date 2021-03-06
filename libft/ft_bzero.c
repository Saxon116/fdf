/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bzero.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:43:52 by nkellum           #+#    #+#             */
/*   Updated: 2018/11/09 18:59:45 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		*(char*)s = '\0';
		s++;
		i++;
	}
}
