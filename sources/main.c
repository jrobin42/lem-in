/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/02 23:20:36 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_list		*path;
	t_ants		ant;
//	int			max_nb_paths;

	ft_bzero(&lemin, sizeof(t_lemin));
	path = NULL;
	if (collect_parse_data(&lemin, &ant) == FAILURE)
		ft_printf("ERROR\n");
//	else if (resolve_lemin(&lemin, lemin.adj_mtx, &path) == FAILURE)
	else if (pathfinding(&lemin, lemin.adj_mtx, &path) == FAILURE)
		ft_printf("ERROR\n");
//	else
//		multi_path(&ant, ant.nb_ants, &lemin, &path);
	//	free_lemin();
//	else
//		print_solution(&ant, path, &lemin);
	return (0);
}

/*Checker les cas d'erreurs evidemment*/
