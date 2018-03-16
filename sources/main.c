/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/17 00:20:34 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_path		path;
	t_ants		ant;

	ft_bzero(&lemin, sizeof(t_lemin));
	ft_bzero(&path, sizeof(t_path));
	if (collect_parse_data(&lemin, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("SUCCESS\n");
	while (lemin.to_print)
	{
		printf("\t%s\n", *((char**)(lemin.to_print->content)));
		lemin.to_print = lemin.to_print->next;
	}
	pathfinding(&path, &lemin, lemin.adj_mtx);
	ft_printf("max nb of paths = %d\n", path.max_nb_paths);
/*	int i = 0;
	int j;
	while (i < lemin.nb_rooms)
	{
		j = 0;
		while (j < lemin.nb_rooms)
		{
			ft_printf("%2d", lemin.adj_mtx[i][j]);
			++j;
		}
		ft_printf("\n");
		++i;
	}
*/	//	free_lemin();
	return (0);
}
