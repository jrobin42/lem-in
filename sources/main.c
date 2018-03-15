/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/15 15:45:36 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_ants		ant;

	ft_bzero(&lemin, sizeof(t_lemin));
	if (collect_parse_data(&lemin, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("SUCCESS\n");
	ft_printf("%d\n", lemin.nb_rooms);
	int i = 0;
	while (i < lemin.nb_rooms)
	{
		ft_printf("%s\n", ((lemin.rooms)[i])->name);
		i++;
	}
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
