/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/11 19:42:53 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_room		room;
	t_ants		ant;

	if (collect_parse_data(&lemin, &room, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("SUCCESS\n");
	ft_printf("END %s\n", ((t_room*)lemin.end->content)->name);
	ft_printf("START %s\n", ((t_room*)lemin.start->content)->name);
/*	while (lemin.all)
	{
		ft_printf("ROOMNAME %s\n", ((t_room*)(lemin.all->content))->name);
		lemin.all = lemin.all->next;
	}
	while (lemin.to_print)
	{
	ft_printf("%s\n", (char*)lemin.to_print->content);
	lemin.to_print = lemin.to_print->next;
	}
*/	//	pathfinding();
	//	free_lemin();
	return (0);
}
