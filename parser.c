/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:49:32 by apion             #+#    #+#             */
/*   Updated: 2018/12/21 19:03:17 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "utils.h"
#include "parser.h"
#include "errors.h"

unsigned short	g_tiles[] =
{
	0b1000100010001000,
	0b1111000000000000,
	0b1100100010000000,
	0b1110001000000000,
	0b0100010011000000,
	0b1000111000000000,
	0b1100010001000000,
	0b1110100000000000,
	0b1000100011000000,
	0b0010111000000000,
	0b1100110000000000,
	0b1100011000000000,
	0b0100110010000000,
	0b0110110000000000,
	0b1000110001000000,
	0b1000110010000000,
	0b0100110001000000,
	0b1110010000000000,
	0b0100111000000000
};

static int	get_left_col(unsigned short v)
{
	int				i;
	unsigned short	mask;

	mask = 0b1000100010001000;
	i = -1;
	while (++i < 4)
	{
		if (((mask >> i) & v) != 0)
			return (i);
	}
	return (-1);
}

static int	get_top_row(unsigned short v)
{
	int		i;

	i = -1;
	while (++i < 16)
	{
		if ((v >> (15 - i)) & 1)
			return (i / 4);
	}
	return (-1);
}

static int	create_tile(t_tile *tetrimino, unsigned short tile)
{
	short	i;

	tetrimino->width = 0;
	tetrimino->height = 0;
	i = -1;
	while (++i < 4)
	{
		tetrimino->lines[i] = ((tile << (4 * i)) >> 12) << 12;
		tetrimino->height += (tetrimino->lines[i] != 0);
		tetrimino->width |= tetrimino->lines[i];
	}
	tetrimino->width = n_bits_on(tetrimino->width);
	return (0);
}

static int	extract_tile(unsigned short tmp, t_tile *tetrimino)
{
	int			i;

	if (!tmp || n_bits_on(tmp) != 4)
		return (1);
	i = -1;
	while (++i < 19)
	{
		if ((tmp << (get_left_col(tmp) + 4 * get_top_row(tmp))) == g_tiles[i])
			return (create_tile(tetrimino, g_tiles[i]));
	}
	return (ERR_TILE);
}

int			parser(t_tile *tiles, int *k, const int fd)
{
	char			buf[SIZE];
	ssize_t			r;
	int				i;
	char			err;
	unsigned short	tmp;

	if ((r = read(fd, buf, SIZE)) < 0 || r > MAP_MAX)
		return (r > MAP_MAX ? ERR_FILE_SIZE : ERR_READ);
	tmp = 0;
	err = 0;
	i = -1;
	while (!err && ++i < r)
	{
		if (i > 0 && i % 21 == 0 && !(err = extract_tile(tmp, &tiles[(*k)++])))
			tmp = 0;
		if (i % 21 < 20 && ((i - *k) % 5) < 4 && buf[i] != '.' && buf[i] != '#')
			return (ERR_CHAR);
		else if (i % 21 < 20 && ((i - *k) % 5) < 4 && buf[i] == '#')
			tmp ^= 1 << (15 - (i % 21) + ((i % 21) / 5));
		if (i % 21 < 20 && ((i - *k) % 5) == 4 && buf[i] != '\n')
			return (ERR_FILE);
		if (i % 21 == 20 && buf[i] != '\n')
			return (ERR_FILE_SIZE);
	}
	return (err || i < 20 || !(r % 21) || extract_tile(tmp, &tiles[(*k)++]));
}
