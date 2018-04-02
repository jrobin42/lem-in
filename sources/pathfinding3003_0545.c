/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 02:31:23 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/30 05:32:07 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			DEBUG_aff_prev(int *prev, int max, int *gap)
{
	int		i;

	i = 0;
	(void)gap;
	(void)prev;
	while (i < max)
	{
			ft_printf("prev[%d] = %d\n", i, prev[i]);
			//ft_printf("gap[%d] = %d\n", i, gap[i]);
		++i;
	}
}

static void		init_tabs(int *prev, int *visited, int *gap, int max)
{
	int		i;

	i = -1;
	while (++i < max)
	{
		prev[i] = -1;
		visited[i] = 0;
		gap[i] = -1;
	}
}

static void		take_smallest_gap(int *gap, int *prev, int *next, int *curr, int max, int *visited)
{
	int		i;
	int		best_gap;
	int		best_room;

	i = 0;
	best_gap = max;
	while (i < max)
	{
		if (gap[i] != -1 && visited[i] == 0 && gap[i] < best_gap)
		{
	ft_printf("gap[%d] = %d\n", i, gap[i]);
			best_gap = gap[i];
			best_room = i;
		}
		++i;
	}
	ft_printf("best = %d\n", best_room);
	prev[best_room] = *curr;
	DEBUG_aff_prev(prev, max, gap);
	*curr = best_room;
	*next = 0;
	sleep(1);
}

static void		change_gap(int *gap, int curr, int next)
{
	if (curr == 0)
		gap[next] = 1;
	else
		gap[next] = gap[curr] + 1;
	ft_printf("current = %d next = %d\n", curr, next);
}

int				all_visit(int *visited, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (visited[i] == 0)
			return (FALSE);
	ft_printf("visited[%d] = %d\n", i, visited[i]);
		++i;
	}
	return (TRUE);
}

static void		path_finding(int *prev, int *visited, int *gap, int max, int **mat)
{
	int		curr;
	int		next;

	curr = 0;
	next = 0;
	while (curr < max - 1 || all_visit(visited, max) == FALSE) //attention si aucun chemin
	{
		while (next < max && all_visit(visited, max) == FALSE)
		{
			if (next != curr && visited[next] == 0 && mat[curr][next] == 1
				&& (gap[next] > gap[curr] + 1 || gap[next] == -1))
			{
				change_gap(gap, curr, next);
			}
			++next;
	//		ft_printf("curr = %d next = %d gap[next] = %d \n", curr, next, gap[next]);
		}
		visited[curr] = 1;
	ft_printf("curr = %d next = %d\n", curr, next);
		take_smallest_gap(gap, prev, &next, &curr, max, visited);
	}
}

int				resolve_lemin(t_lemin *lemin, int **mat, t_path **path)
{
	int		prev[lemin->nb_rooms];
	int		visited[lemin->nb_rooms];
	int		gap[lemin->nb_rooms];

	(void)path;
	init_tabs(prev, visited, gap, lemin->nb_rooms);
	path_finding(prev, visited, gap, lemin->nb_rooms, mat);
	return (SUCCESS);
}
