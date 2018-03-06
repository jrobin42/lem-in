/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/06 17:04:12 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_room		room;
	t_ants		ant;

//	while (1)
	{
		ant.nb_ants = 1000;
		if (collect_parse_data(&lemin, &room, &ant))
		{
			ft_printf("ERROR {%d}\n", ant.nb_ants);
		}
		else
			ft_printf("SUCCESS {%d}\n", ant.nb_ants);
	}
	//	pathfinding();
	//	free_lemin();
	return (0);
}
