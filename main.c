/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:36:40 by apion             #+#    #+#             */
/*   Updated: 2018/12/22 12:42:35 by jkettani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "parser.h"
#include "solver.h"
#include "errors.h"

static int	print_usage(char *exec)
{
	print_str("usage:\t");
	print_str(exec);
	print_str(" file\n");
	return (-1);
}

static int	print_err(int err)
{
	if (!ERR_ACTIVE)
	{
		print_str("error\n");
		return (-1);
	}
	if (err == ERR_TILE)
		print_str("error: invalid tetrimino\n");
	else if (err == ERR_CHAR)
		print_str("error: invalid character (only '.' and '#')\n");
	else if (err == ERR_FILE)
		print_str("error: invalid file (columns > 4 characters)\n");
	else if (err == ERR_FILE_SIZE)
		print_str("error: invalid file (too long)\n");
	else if (err == ERR_OPEN)
		print_str("error: could not open file\n");
	else if (err == ERR_CLOSE)
		print_str("error: could not close file\n");
	else if (err == ERR_READ)
		print_str("error: could not read from file\n");
	else if (err == ERR_MALLOC)
		print_str("error: not sufficient space to malloc\n");
	else
		print_str("error\n");
	return (-1);
}

int			main(int ac, char **av)
{
	int		fd;
	t_tile	tiles[26];
	int		nb_tiles;
	int		err;

	if (ac != 2)
		return (print_usage(av[0]));
	nb_tiles = 0;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (print_err(ERR_OPEN));
	err = parser(tiles, &nb_tiles, fd);
	if (err)
		return (print_err(err));
	if ((err = solver(tiles, nb_tiles)) != 1)
		print_err(err);
	if (close(fd) == -1)
		print_err(ERR_CLOSE);
	return (0);
}
