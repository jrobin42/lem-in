/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/29 00:17:45 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_lemin(t_lemin l)
{
	ft_lstdel(&(l.to_print), &del_to_print);
	if (l.rooms)
	{
		ft_free_tab((void***)&(l.data));
		ft_lstdel(&(l.all), NULL);
		free_rooms(l.rooms, l.nb_rooms);
	}
	else
		ft_lstdel(&(l.all), &del);
}

int		main(void)
{
	char		*line;
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	line = NULL;
	if (get_nb_ants(&line, &lemin) == FAILURE)
	{
		ft_strdel(&line);
		ft_printf("ERROR : WRONG INPUT\n%s\n", lemin.error_type);
		return (FAILURE);
	}
	if (collect_parse_data(&lemin, line) == FAILURE)
	{
		ft_printf("ERROR : WRONG INPUT\n%s\n", lemin.error_type);
		free_lemin(lemin);
		return (1);
	}
	else if (!lemin.adj_mtx || resolve_lemin(&lemin, lemin.adj_mtx) == FAILURE)
	{
		ft_printf("ERROR : NO SOLUTION\n");
		free_lemin(lemin);
		return (1);
	}
	free_lemin(lemin);
	return (0);
}
