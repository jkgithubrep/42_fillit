/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apion <apion@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 13:48:35 by apion             #+#    #+#             */
/*   Updated: 2018/12/21 17:52:23 by apion            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H

# include "utils.h"

char	*init_str(int n);
int		set_char(char *str, t_tile *tile, int i, t_map *map);

#endif
