/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:06:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/15 15:39:22 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		create_adjacency_matrix(t_room ***rooms, t_lemin *lemin)
{
	int		i;
	t_room	**tmp;

	i = 0;
	if ((tmp = ft_memalloc((lemin->nb_rooms + 1) * sizeof(t_room*))) == NULL)
		return (FAILURE);
	tmp[0] = lemin->start->content;
	tmp[lemin->nb_rooms - 1] = lemin->end->content;
	while (lemin->all)
	{
		if (((t_room*)lemin->all->content) != lemin->start->content && ((t_room*)lemin->all->content) != lemin->end->content)
			tmp[++i] = (t_room*)lemin->all->content;
		lemin->all = lemin->all->next;
	}
	STEP = 2;
	*rooms = tmp;
	return (SUCCESS);
}
