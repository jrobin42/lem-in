/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/29 00:19:49 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/29 03:17:16 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			print_ants_distribution(int *nb_paths, int **ants_for_each)
{
	int		i;

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

void			usefull_paths(int **ants_for_each, int nb_ants, int *len_p,
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
	print_ants_distribution(nb_paths, ants_for_each);
}

void			pull_ant(int nb_ants, t_room **r, int *path, int len_p)
{
	int		i;

	i = -1;
	while (++i < len_p)
	{
		if (i == 0 && r[path[1]]->ant > 0)
		{
			if (r[path[i + 1]]->ant > r[path[i]]->ant &&
			(r[path[i]]->ant = r[path[i + 1]]->ant))
				ft_printf("L%d-%s ", r[path[0]]->ant, r[path[0]]->name);
			else
				ft_printf("L%d-%s ", r[path[1]]->ant, r[path[0]]->name);
			r[path[1]]->ant = 0;
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
