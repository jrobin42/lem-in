/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/31 21:17:32 by jrobin           ###   ########.fr       */
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

void	DEBUG_aff_prev(int *prev, int max, t_lemin *lemin, int *visited)
{
	int	i;

	(void)lemin;
	(void)prev;
	(void)visited;
	i = max - 1;
	ft_printf("PATH :\n");
	while (i > 0)
	{
		//		ft_printf("Visited[%d] = %d\n", i, visited[i]);
		if (i != -1)
			ft_printf("PREV[%d] = %d\n", i, prev[i]);
		i = prev[i];
		//		ft_printf("%s\n", (lemin->rooms)[prev[i]]->name);
	}
}

void		aff_mat(int **mat, int x, int y, int max)
{
	while (++y < max)
	{
		x = -1;
		while (++x < max)
			ft_printf("%2d ", mat[y][x]);
		ft_printf("\n");
	}
	ft_printf("\n");
}

static void		set_curr_value(int *curr, int *visited, int *prev, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (prev[i] == *curr && visited[i] == 0)
		{
			*curr = i;
			break ;
		}
		++i;
	}
}

static int		find_one_path(int *prev, int *gap, int *visited, t_lemin *lemin, int **mat)
{
	int		curr;
	int		curr;
	int		next;

	curr = 0;
	next = 0;
	while (curr < MAX)
	{
		while (next < MAX)
		{
			if (curr != next && visited[next] == 0 && mat[curr][next] == 1)
			{
				if (gap[next] == -1 || gap[next] > gap[curr] + 1)
				{
					gap[next] = gap[curr] + 1;
				}
			}
			++next;
		}
		visited[curr] = 1;
		set_curr_value(&curr, visited, prev);
	}
	return (SUCCESS);
}

int		pathfinding(t_lemin *lemin, int **mat, t_list **path)
{
	int		curr;
	int		next;
	int		prev[lemin->nb_rooms];
	int		gap[lemin->nb_rooms];
	int		visited[lemin->nb_rooms];
	int		i;
	int		j;

	init_tab(prev, gap, visited, lemin->nb_rooms);
	find_one_path(prev, gap, visited, lemin, mat);
	return (SUCCESS);
}
