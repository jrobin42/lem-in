/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 04:39:53 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/25 23:36:32 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		print_solution(t_list *path, t_lemin *lemin)
{
//	int i = 0;
	//int j;
	//int a = 0;
/*	while (i < lemin->nb_rooms)
	{
		j = 0;
		while (j < lemin->nb_rooms)
		{
			while (i == 0 && a != 2 && j < lemin->nb_rooms)
			{
				if (a == 0 && ++a)
					ft_printf("\nROOM NUMBER :\n");
				ft_printf("%d ", j);
				++j;
				if (j == lemin->nb_rooms)
				{
					j = 0;
					a = 2;
		ft_printf("\n\n");
					break ;
				}
			}
			ft_printf("%d ", lemin->adj_mtx[i][j]);
			++j;
		}
		ft_printf("\n");
		++i;
	}*/
	while (lemin->to_print)
	{
		printf("%s\n", *((char**)(lemin->to_print->content)));
		lemin->to_print = lemin->to_print->next;
	}
	path = path->next;
/*	while (path)
	{
		i = 0;
		ft_printf("gooooooooooooood\n");
		while (((int*)path->content)[i] != -1)
		{
		ft_printf("out\n");
			ft_printf("path[i] : %d\n", ((int*)path->content)[i]);
			++i;
		}
		path = path->next;
	}
*/	return (SUCCESS);
}
