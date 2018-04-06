/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_soluce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:53:37 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/06 06:08:46 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_input(t_list *to_print, int step)
{
	while (to_print)
	{
		if (to_print->next == NULL && step == 42)
			break ;
		ft_printf("%s\n", (char*)to_print->content);
		to_print = to_print->next;
	}
}

static void			print_curr_state(t_room **rooms, int len_paths)
{
	int		i;

	i = len_paths;
	while (i > 0)
	{
		if (rooms[i]->ant)
			ft_printf("L%d-%s ", rooms[i]->ant, rooms[i]->name);
		--i;
	}
	ft_printf("\n");
}

void				print_soluce(int **paths, t_lemin *l, int nb_paths,
								int *len_p)
{
	int		i;
	int		nb;
	int		*tmp;
	t_room	**r;

	nb = 0;
	r = l->rooms;
	(void)nb_paths;
	tmp = *paths;
	print_input(l->to_print, l->step);
	r[0]->ant = l->nb_ants;
	while (nb < l->nb_ants)
	{
		print_curr_state(r, *len_p);
		i = -1;
		while (++i < *len_p)
			if (i == 0 && r[tmp[1]]->ant > 0 && ++nb)
			{
				r[tmp[i]]->ant = r[tmp[i + 1]]->ant;
				r[tmp[i + 1]]->ant = 0;
			}
			else if (i == *len_p - 1 && r[tmp[i]]->ant == 0 && r[0]->ant > 0)
			{
				r[tmp[i]]->ant = l->nb_ants - r[tmp[i + 1]]->ant + 1;
				r[tmp[i + 1]]->ant -= 1;
			}
			else if (r[tmp[i]]->ant == 0)
			{
				r[tmp[i]]->ant = r[tmp[i + 1]]->ant;
				r[tmp[i + 1]]->ant = 0;
			}
		++i;
	}
	print_curr_state(r, *len_p);
}
