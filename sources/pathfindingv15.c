/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/29 10:26:47 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_tab(int *prev, int *gap, int *visited, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		prev[i] = -1;
		gap[i] = -1;
		visited[i] = 0;
		++i;
	}
	gap[0] = 0;
	visited[0] = 1;
}


int		pathfinding(t_lemin *lemin, int **mat, t_path *path)
{
	int		curr;
	int		next;
	int		prev[lemin->nb_rooms];
	int		gap[lemin->nb_rooms];
	int		visited[lemin->nb_rooms];

	curr = 0;
	init_tab(prev, gap, visited, lemin->nb_rooms);
	while (curr < lemin->nb_rooms - 1)
	{
		next = 0;
		while (next < lemin->nb_rooms)
		{
			if (next != curr && visited[next] == 0 && (gap[next] == -1
						|| (gap[curr] + 1) < gap[next]))
			{
				prev[next] = curr;
				gap[next] = gap[curr] + 1;
			}
			++next;
		}
	}
	return (SUCCESS);
}
