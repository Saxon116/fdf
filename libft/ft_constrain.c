/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_constrain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:25:59 by nkellum           #+#    #+#             */
/*   Updated: 2019/02/04 12:34:01 by nkellum          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_constrain(int val, int min, int max)
{
	if (val >= max)
		return (max);
	if (val <= min)
		return (min);
	return (val);
}
