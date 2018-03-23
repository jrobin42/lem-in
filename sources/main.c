/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/23 14:00:32 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_list		*path;
	t_ants		ant;
	int			max_nb_paths;
	//t_path		data_path;

	ft_bzero(&lemin, sizeof(t_lemin));
	path = NULL;
	//ft_bzero(&data_path, sizeof(t_path));
	//((t_path*)path.content) = data_path;
	if (collect_parse_data(&lemin, &ant))
		ft_printf("ERROR\n");
	else
		ft_printf("EiiiiiiiiiiiRROR\n");
	pathfinding(path, &lemin, lemin.adj_mtx, &max_nb_paths);
	print_solution(path, &lemin, max_nb_paths);
	
	//	free_lemin();
	return (0);
}
