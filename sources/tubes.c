/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:06:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/13 15:40:53 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		create_adjacency_matrix(t_lemin *lemin)
{
	int		i;
	t_room	**rooms;

	i = 0;
	if ((rooms = ft_memalloc((lemin->nb_rooms + 1) * sizeof(t_room*))) == NULL)
		return (FAILURE);
	rooms[0] = lemin->start->content;
	rooms[lemin->nb_rooms - 1] = lemin->end->content;
	while (++i < lemin->nb_rooms - 1)
	{
		if (((t_room*)lemin->all->content) != lemin->start->content && ((t_room*)lemin->all->content) != lemin->end->content)
			rooms[i] = (t_room*)lemin->all->content;
		else
			--i;
		lemin->all = lemin->all->next;
	}
	i = 0;
	while (i < lemin->nb_rooms)
	{
		ft_printf("HEHE%d %s\n", i, (rooms[i])->name);
		++i;
	}
	STEP = 2;
	return (SUCCESS);
}
