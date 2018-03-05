/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/05 19:42:35 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_rooms		room;
	t_ants		ant;

	if (collect_parse_data(&lemin, &room, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("SUCCESS {%d}\n", ant.nb_ants);
//	pathfinding();
//	free_lemin();
	return (0);
}
