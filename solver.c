/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:11:19 by apion             #+#    #+#             */
/*   Updated: 2018/12/22 12:39:11 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "output.h"
#include "errors.h"

static void	toggle_tile(t_map *map, t_tile *tile)
{
	int		i;

	i = -1;
	while (++i < tile->height)
		map->lines[tile->y + i] ^= (tile->lines[i] >> tile->x);
}

static int	check_tile(t_map *map, t_tile *tile)
{
	int		h;
	int		err;

	err = 0;
	h = tile->height;
	while (h-- && !err)
		err = map->lines[tile->y + h] & (tile->lines[h] >> tile->x);
	return (!err);
}

static int	fillit(t_map *map, t_tile *tiles, int k, int i)
{
	int				ret;
	static char		*out;

	if (i == k)
		return ((out = init_str(map->n)) ? 1 : ERR_MALLOC);
	tiles[i].y = 0;
	while ((tiles[i].y + tiles[i].height) <= map->n)
	{
		tiles[i].x = 0;
		while ((tiles[i].x + tiles[i].width) <= map->n)
		{
			if (check_tile(map, &tiles[i]))
			{
				toggle_tile(map, &tiles[i]);
				if ((ret = fillit(map, tiles, k, i + 1)) == ERR_MALLOC)
					return (ERR_MALLOC);
				else if (ret)
					return (set_char(out, &tiles[i], i, map));
				toggle_tile(map, &tiles[i]);
			}
			++(tiles[i].x);
		}
		++(tiles[i].y);
	}
	return (0);
}

int			solver(t_tile *tiles, int k)
{
	int				ret;
	static t_map	map;

	ret = 0;
	map.n = get_width_max(tiles, k);
	while (map.n * map.n < 4 * k)
		map.n++;
	while (!(ret = fillit(&map, tiles, k, 0)))
		map.n++;
	return (ret);
}
