/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 00:30:55 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(void)
{
	t_lemin		lemin;
	t_list		*path;
	t_ants		ant;
	int			max_nb_paths;

	ft_bzero(&lemin, sizeof(t_lemin));
	path = NULL;
	if (collect_parse_data(&lemin, &ant) == FAILURE)
		ft_printf("ERROR\n");
	else if (pathfinding(&path, &lemin, lemin.adj_mtx, &max_nb_paths) == FAILURE)
		ft_printf("ERROR\n");
	else
		multi_path(ant.nb_ants, &lemin, &path);
	//	free_lemin();
	return (0);
}

/*Checker les cas d'erreurs evidemment*/
