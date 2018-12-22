/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:47:48 by apion             #+#    #+#             */
/*   Updated: 2018/12/21 18:37:32 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static void	print_solution(char *str)
{
	print_str(str);
	free((void *)str);
}

char		*init_str(int n)
{
	int		i;
	int		l;
	char	*str;

	l = n * (n + 1);
	str = (char *)malloc(sizeof(*str) * (l + 1));
	if (!str)
		return (0);
	i = -1;
	while (++i < l)
	{
		if (i && (i + 1) % (n + 1) == 0)
			*(str + i) = '\n';
		else
			*(str + i) = '.';
	}
	*(str + i) = 0;
	return (str);
}

int			set_char(char *str, t_tile *tile, int i, t_map *map)
{
	int				start;
	int				j;
	int				h;
	unsigned short	mask;

	if (!str)
		return (0);
	h = -1;
	while (++h < tile->height)
	{
		start = tile->x + (tile->y + h) * (map->n + 1);
		j = -1;
		mask = 1 << (sizeof(mask) * 8 - 1);
		while (++j < tile->width)
			if (tile->lines[h] & (mask >> j))
				*(str + start + j) = 'A' + i;
	}
	if (i == 0)
		print_solution(str);
	return (1);
}
