/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_solution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 04:39:53 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/29 07:10:58 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
/*
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
   */
static void		print_curr_state(int max, int *p_curr_state, t_room **rooms, int *path)
{
	int		i;
	int		j;

	i = max - 1;
	j = 0;
	while (i > 0)
	{
		if (p_curr_state[i] != 0)
			ft_printf("L%d-%s ", p_curr_state[i], rooms[path[j]]->name);
		++j;
		--i;
	}
	ft_printf("\n");
}

int		print_solution(t_ants *ants, t_path *path, t_lemin *lemin)
{
	int		i;
	int		max;
	int		x;
	int		*p_curr_state;
	t_path	*tmp;

	max = 0;
	i = -1;
	tmp = path;
	while (++i < lemin->nb_rooms && path->path[i] != 0)
		++max;
	p_curr_state = ft_memalloc((max + 1) * sizeof(int));
	p_curr_state[0] = 1;
	while (p_curr_state[max] < ants->nb_ants)
	{
	//	ft_printf("nb ants %d nb ants in end %d\n", ants->nb_ants, p_curr_state[max]);
		while (tmp)
		{
		x = max + 1;
		while (--x)
		{
			if (x == max && p_curr_state[x - 1])
			{
				p_curr_state[max] += 1;
				p_curr_state[max - 1] = 0;
			}
			else if (p_curr_state[x] == 0)
			{
				p_curr_state[x] = p_curr_state[x - 1];
				x == 1 && p_curr_state[x]? (p_curr_state[0] += 1) : (p_curr_state[x - 1] = 0);
			}
			if (p_curr_state[0] > ants->nb_ants)
				p_curr_state[0] = 0;
		}	
			int plop = 0;
			while (plop < max + 1)
			{
			ft_printf("%d ", p_curr_state[plop]);
			plop++;
			}
			ft_printf("\n");
		print_curr_state(max, p_curr_state, lemin->rooms, tmp->path);
			ft_printf("tmp next\n");
		tmp = tmp->next;
		}
		tmp = path;
	}
	ft_printf("%p\n", path);
	ft_printf("%p\n", tmp);
	while (path)
	{
	i = 0;
	while (i < max)
	{
		ft_printf("%d\n", path->path[i]);
		++i;
	}
	ft_printf("\n");
	path = path->next;
}
return (SUCCESS);
}
