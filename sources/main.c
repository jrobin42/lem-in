/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/20 05:52:19 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_list		path;
	t_ants		ant;
	int			max_nb_paths;

	ft_bzero(&lemin, sizeof(t_lemin));
	ft_bzero(&path, sizeof(t_list));
	if (collect_parse_data(&lemin, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("SUCCESS\n");
	while (lemin.to_print)
	{
		printf("\t%s\n", *((char**)(lemin.to_print->content)));
		lemin.to_print = lemin.to_print->next;
	}
	pathfinding(&path, &lemin, lemin.adj_mtx, &max_nb_paths);
	print_solution(&path, &lemin, max_nb_paths);
	
	//	free_lemin();
	return (0);
}
