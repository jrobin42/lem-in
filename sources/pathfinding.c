/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/03 00:21:20 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_tab(int *prev, int *gap, int *visited, int *next_curr, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		next_curr[i] = -1;
		prev[i] = -1;
		gap[i] = -1;
		visited[i] = 0;
		++i;
	}
	gap[0] = 0;
	visited[0] = 1;
}

void		aff_prev(int *prev, int *gap, int max)
{
	int		i;

	i = 0;
	(void)prev;
	(void)gap;
	while (i < max)
	{
		ft_printf("prev[%d] = %d\n", i, prev[i]);
	//	ft_printf("gap[%d] = %d\n", i, gap[i]);
		++i;
	}
}

void				set_next_curr(int *next_curr, int new, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (next_curr[i] == new)
			return ;
		if (next_curr[i] == -1)
		{
			next_curr[i] = new;
			return ;
		}
		++i;
	}
}

int		pathfinding(t_lemin *lemin, int **mat, t_list **path)
{
	int		i;
	int		curr;
	int		next;
	int		next_curr[lemin->nb_rooms];
	int		prev[lemin->nb_rooms];
	int		gap[lemin->nb_rooms];
	int		visited[lemin->nb_rooms];

	i = 0;
	curr = 0;
	(void)path;
	init_tab(prev, gap, visited, next_curr, lemin->nb_rooms);
	while (curr < lemin->nb_rooms - 1)
	{
		next = 0;
		while (next < lemin->nb_rooms)
		{
			if (next != curr && visited[next] == 0 && mat[curr][next] == 1)
			{
				if (gap[next] == -1 || (gap[curr] + 1) < gap[next])
				{
					if (curr == 0)
						gap[next] = 1;
					else
						gap[next] = gap[curr] + 1;
					prev[next] = curr;
					set_next_curr(next_curr, next, lemin->nb_rooms);
					ft_printf("curr = %d next = %d\n", curr, next);
				}
			}
			++next;
		}
		visited[curr] = 1;
		curr = next_curr[i];
		++i;
	}
	aff_prev(prev, gap, lemin->nb_rooms);
	return (SUCCESS);
}
