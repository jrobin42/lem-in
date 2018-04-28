/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_soluce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:53:37 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/29 01:04:33 by jrobin           ###   ########.fr       */
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
	ft_printf("\n");
}

static void			print_curr_state(t_room **r, int **t, int *len_path,
				int nb_paths)
{
	int		i;
	int		j;

	j = 0;
	while (j < nb_paths)
	{
		i = 1;
		while (i < len_path[j])
		{
			if (r[t[j][i]]->ant)
				ft_printf("L%d-%s ", r[t[j][i]]->ant, r[t[j][i]]->name);
			++i;
		}
		++j;
	}
	ft_printf("\n");
	(void)nb_paths;
}

void				print_direct_path(int nb_ants, t_room **r, int end)
{
	int		i;

	i = 0;
	while (++i <= nb_ants)
		ft_printf("L%d-%s ", i, r[end]->name);
	ft_printf("\n");
}

void				print_soluce(int **paths, t_lemin *l, int nb_p,
		int *len_p)
{
	int		i;
	int		index_p;
	int		*ants_for_each;
	t_room	**r;

	index_p = 0;
	r = l->rooms;
	if ((ants_for_each = ft_memalloc(nb_p * sizeof(int))) == NULL)
		exit(-1);
	nb_p > 1 ? usefull_paths(&ants_for_each, l->nb_ants, len_p, &nb_p) : 0;
	print_input(l->to_print, l->step);
	r[0]->ant = l->nb_ants;
	if (*len_p > 1)
		while (r[l->nb_rooms - 1]->ant < l->nb_ants)
		{
			i = -1;
			while (++i < nb_p)
				pull_ant(l->nb_ants, r, paths[i], len_p[i]);
			print_curr_state(r, paths, len_p, nb_p);
		}
	else
		print_direct_path(l->nb_ants, r, **paths);
	free(ants_for_each);
}

void				aff_paths(t_lemin *l, int **path, int *len_paths,
			int nb_paths)
{
	int		i;
	int		j;

	j = 0;
	ft_printf("There is %d", nb_paths - 1);
	nb_paths - 1 > 1 ? ft_printf(" paths :\n\n") : ft_printf(" path :\n\n");
	while (nb_paths - 1)
	{
		ft_printf("\tPath no %d :\t%s->", j, l->rooms[0]->name);
		i = len_paths[j] - 1;
		while (i > 0)
		{
			ft_printf("%s->", l->rooms[path[j][i]]->name);
			--i;
		}
		ft_printf("%s\n", l->rooms[path[j][i]]->name);
		--nb_paths;
		++j;
	}
	ft_printf("\n\n");
}
