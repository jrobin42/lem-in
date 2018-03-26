/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 04:39:53 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 00:47:21 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_solution(t_list *path, t_lemin *lemin)
{
	int		i;

	while (lemin->to_print)
	{
		printf("%s\n", *((char**)(lemin->to_print->content)));
		lemin->to_print = lemin->to_print->next;
	}
	while (path)
	{
		i = 0;
		while (i < lemin->nb_rooms && PATH->path[i] != -1)
		{
			ft_printf("path[%d] : %d\n", i, PATH->path[i]);
			++i;
		}
		ft_printf("pathinext: %p\n", PATH);
		path = path->next;
	}
	return (SUCCESS);
}
