/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_soluce.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 05:53:37 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/27 19:15:44 by jrobin           ###   ########.fr       */
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

static void			print_curr_state(t_room **r, int **t, int *len_path, int nb_paths)
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
	i = 0;
	ft_printf("Ants distribution :\n\n");
	while (i < *nb_paths)
	{
		ft_printf("\tFor path no %d : %d", i, (*ants_for_each)[i]);
		ft_printf((*ants_for_each)[i] == 1 ? " ant\n" : " ants\n");
		++i;
	}
	ft_printf("\n\n");
}

static void			pull_ant(int nb_ants, t_room **r, int *path, int len_p)
{
	int		i;

	i = -1;
	while (++i < len_p)
	{
		if (i == 0 && r[path[1]]->ant > 0)
		{
			if (r[path[i + 1]]->ant > r[path[i]]->ant)
			{
				r[path[i]]->ant = r[path[i + 1]]->ant;
				ft_printf("L%d-%s ", r[path[0]]->ant, r[path[0]]->name);
			}
			else
				ft_printf("L%d-%s ", r[path[i + 1]]->ant, r[path[i]]->name);
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
}

void				print_direct_path(int nb_ants, t_room **r, int end)
{
	int		i;

	i = 0;
	while (++i <= nb_ants)
		ft_printf("L%d-%s ", i, r[end]->name);
	ft_printf("\n");
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
	if ((ants_for_each = ft_memalloc(nb_paths * sizeof(int))) == NULL)
		exit(-1);
	if (nb_paths > 1)
		usefull_paths(&ants_for_each, l->nb_ants, len_p, &nb_paths);
	print_input(l->to_print, l->step);
	r[0]->ant = l->nb_ants;
	if (*len_p > 1)
	{
		while (r[l->nb_rooms - 1]->ant < l->nb_ants)
		{
			i = 0;
			while (i < nb_paths)
			{
				pull_ant(l->nb_ants, r, paths[i], len_p[i]);
				++i;
			}
			print_curr_state(r, paths, len_p, nb_paths);
		}
	}
	else
		print_direct_path(l->nb_ants, r, **paths);
	free(ants_for_each);
}
