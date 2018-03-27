/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 04:39:53 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 20:49:09 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		count_paths(t_list *path)
{
	int		count;

	count = 0;
	while (path)
	{
		++count;
		path = path->next;
	}
	return (count);
}
/*
static void		prepare_ants(int **w_ants, t_list *path)
{
	int		nb_paths;

	nb_paths = count_paths(path);
	*w_ants = ft_memalloc(nb_paths * sizeof(int));
}
*/
int		print_solution(t_ants *ants, t_list *path, t_lemin *lemin)
{
	int		i;
	int		r_ants;
	int		count;
	int		tmp;
	int		tmp_num;
//	int		*w_ants;
	t_list	*begin;

	begin = path;
	while (lemin->to_print)
	{
		printf("%s\n", *((char**)(lemin->to_print->content)));
		lemin->to_print = lemin->to_print->next;
	}
//	prepare_ants(&w_ants);
	i = 1;
	r_ants = ants->nb_ants - 1;
	count = count_paths(path);
	tmp = count;
	PATH->num_ant = ants->nb_ants - r_ants;
	tmp_num = ants->nb_ants - r_ants;
	path =begin;
	while (path)
	{
		i = 0;
		ft_printf("PATH \n");
		while (i < lemin->nb_rooms && PATH->path[i] != -1)
		{
			ft_printf("%d ", PATH->path[i]);
			++i;
		}
		ft_printf("\n");
		path = path->next;
	}
		ft_printf("ppppppppppppp\n");

















//	ft_printf("-%p\n ", (lemin->rooms)[1]);
//	while (ants->nb_ants)
//	{
//		while (tmp)
//		{
//			ft_printf("-%p\n ", (lemin));
//			ft_printf("L%d-%s ", PATH->num_ant,
//				   	(lemin->rooms)[PATH->path[i]]->name);
//			path = path->next;
//*			if (path)
//			{
/*				++tmp_num;
				PATH->num_ant = tmp_num;
			}
*//*			--tmp;
		}
		tmp = 1;
		path = begin;
	}*/
	return (SUCCESS);
}
