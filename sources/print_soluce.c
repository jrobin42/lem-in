/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_soluce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:53:37 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 16:00:08 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void			print_input(t_list *to_print, int step)
{
	t_list	*prev;

	while (to_print)
	{
		prev = to_print;
		if (to_print->next == NULL && step == 42)
			break ;
		ft_printf("%s\n", (char*)to_print->content);
		ft_strdel((char**)&(to_print->content));
		to_print = to_print->next;
		free(prev);
		prev = NULL;
	}
	ft_strdel((char**)&(to_print->content));
	free(to_print);
	free(prev);
	ft_printf("\n");
}

static void			print_curr_state(t_room **r, int *t, int len_path, int nb_paths)
{
	int		i;

	i = 0;
	while (i < len_path)
	{
		if (r[t[i]]->ant)
			ft_printf("L%d-%s ", r[t[i]]->ant, r[t[i]]->name);
		++i;
	}
	(void)nb_paths;
}

void				usefull_paths(int **ants_for_each, int nb_ants, int *len_p,
		int *nb_paths)
{
	int		i;
	int		placed_ants;

	i = 0;
	placed_ants = 0;
	while (placed_ants < nb_ants)
	{
		while (i + 1 < *nb_paths && len_p[i] + (*ants_for_each)[i]
				<= len_p[i + 1] + (*ants_for_each)[i + 1])
		{
			++(*ants_for_each)[i];
			++placed_ants;
		}
		if (i + 1 == *nb_paths)
		{
			++(*ants_for_each)[i];
			++placed_ants;
		}
		i = i + 1 == *nb_paths ? 0 : i + 1;
	}
	i = 0;
	while (i < *nb_paths && (*ants_for_each)[i])
		++i;
	*nb_paths = i;

	/*Aff nb for each path !*/
	i = 0;
	while (i < *nb_paths)
	{
		//		ft_printf("Nb ants for path %d = %d\n", i, (*ants_for_each)[i]);
		++i;
	}
}

static void			pull_ant(int nb_ants, t_room **r, int *path, int len_p)
{
	int		i;
	int		nb;

	nb = 0;
	i = -1;
	while (++i < len_p)
		if (i == 0 && r[path[1]]->ant > 0 && ++nb)
		{
			r[path[i]]->ant = r[path[i + 1]]->ant;
			r[path[i + 1]]->ant = 0;
		}
		else if (i == len_p - 1 && r[path[i]]->ant == 0 && r[0]->ant > 0)
		{
			r[path[i]]->ant = nb_ants - r[path[i + 1]]->ant + 1;
			r[path[i + 1]]->ant -= 1;
		}
		else if (r[path[i]]->ant == 0 && r[path[i + 1]]->ant)
		{
			r[path[i]]->ant = r[path[i + 1]]->ant;
			r[path[i + 1]]->ant = 0;
		}
}

void				print_soluce(int **paths, t_lemin *l, int nb_paths,
		int *len_p)
{
	int		i;
	int		index_p;
	int		*ants_for_each;
	t_room	**r;

	index_p = 0;
	r = l->rooms;
	print_input(l->to_print, l->step);
	if ((ants_for_each = ft_memalloc(nb_paths * sizeof(int))) == NULL)
		exit(-1);
	if (nb_paths > 1)
		usefull_paths(&ants_for_each, l->nb_ants, len_p, &nb_paths);
	r[0]->ant = l->nb_ants;
	while (r[l->nb_rooms - 1]->ant < l->nb_ants)
	{
		i = 0;
		while (i < nb_paths)
		{
			pull_ant(l->nb_ants, r, paths[i], len_p[i]);
			print_curr_state(r, paths[i], len_p[i], nb_paths);
			++i;
		}
		ft_printf("\n");
	}
	free(ants_for_each);
	i = -1;
	while (++i < l->nb_rooms)
	{
		ft_strdel(&(l->rooms[i]->name));
		ft_memdel((void**)&(l->rooms[i]));
	}
}
