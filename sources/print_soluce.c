/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_soluce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:53:37 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/09 21:42:54 by jrobin           ###   ########.fr       */
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

static void			print_curr_state(t_room **r, int *t, int len_path)
{
	int		i;

	i = 0;
	while (i < len_path)
	{
		if (r[t[i]]->ant)
			ft_printf("L%d-%s ", r[t[i]]->ant, r[t[i]]->name);
		++i;
	}
	ft_printf("\n");
}

void				usefull_paths(int **ants_for_each, int nb_ants, int *len_p,
		int nb_paths)
{
	int		steps_p1;
	int		steps_p2;

	(void)nb_paths;
	steps_p1 = len_p[0] + nb_ants;
	steps_p2 = len_p[1];
	while (steps_p2 < steps_p1)
	{
		--steps_p1;
		++steps_p2;
		++(*ants_for_each)[1];
	}
	**ants_for_each = nb_ants - (*ants_for_each)[1];
	ft_printf("NB ants in first path ====  %d\n", (*ants_for_each)[0]);
	ft_printf("NB ants in second path ==== %d\n", (*ants_for_each)[1]);
}

void				print_soluce(int **paths, t_lemin *l, int nb_paths,
		int *len_p)
{
	int		i;
	int		nb;
	int		*tmp;
	int		*ants_for_each;
	t_room	**r;

	tmp = paths[0];
	r = l->rooms;
	nb = 0;
	print_input(l->to_print, l->step);
	if (nb_paths > 1 && l->nb_ants >= len_p[1])
	{
		if ((ants_for_each = ft_memalloc(nb_paths * sizeof(int))) == NULL)
			exit(-1);
		usefull_paths(&ants_for_each, l->nb_ants, len_p, nb_paths);
	}
	r[0]->ant = l->nb_ants;
	while (nb < l->nb_ants)
	{
		print_curr_state(r, tmp, *len_p);
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
			else if (r[tmp[i]]->ant == 0 && r[tmp[i + 1]]->ant)
			{
				r[tmp[i]]->ant = r[tmp[i + 1]]->ant;
				r[tmp[i + 1]]->ant = 0;
			}
		++i;
	}
	print_curr_state(r, tmp, *len_p);
}
