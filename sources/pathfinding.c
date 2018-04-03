/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/03 02:51:46 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_tab(int *prev, int *gap, int *next_curr, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		next_curr[i] = -1;
		prev[i] = -1;
		gap[i] = -1;
		++i;
	}
}

static int		count_paths(int **mat, int max)
{
	int		i;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	i = 1;
	while (i < max)
	{
		if (mat[0][i] == 1)
			++count1;
		++i;
	}
	i = 0;
	while (i < max - 1)
	{
		if (mat[max - 1][i] == 1)
			++count2;
		++i;
	}
	ft_printf("%d, %d\n", count1, count2);
	return (count1 < count2 ? count1 : count2);
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

int			find_shortest_path(int *prev, int **mat,  int max)
{
	int		i;
	int		curr;
	int		next;
	int		next_curr[max];
	int		gap[max];

	i = 0;
	curr = 0;
	init_tab(prev, gap, next_curr, max);
	while (curr < max - 1 && curr > -1)
	{
		next = -1;
		while (++next < max)
			if (next != curr && mat[curr][next] == 1)
				if (gap[next] == -1 || (gap[curr] + 1) < gap[next])
				{
					gap[next] = curr == 0 ? 1 : gap[curr] + 1;
					prev[next] = curr;
					set_next_curr(next_curr, next, max);
				}
		curr = next_curr[i];
		++i;
	}
	return (curr == max - 1 && curr != -1? SUCCESS : FAILURE);
}

void	save_path(int *path, int *reverse_path, int max)
{
	int		i;
	int		j;

	i = 1;
	j = max - 1;
	path[0] = max - 1;
	while (i < max && j > 0)
	{
		path[i] = reverse_path[j];
		j = reverse_path[j];
		ft_printf("chemin : %d\n", path[i]);
		++i;
	}
	ft_printf("\n");
}

void	delete_access(int **mat, int *cell, int max)
{
	int		i;
	int		j;

	i = 0;
	(void)mat;
	while (i < max && cell[i])
	{
	ft_printf("cell = %d\n", cell[i]);
		j = -1;
		while (++j < max)
			mat[i][cell[j]] = 0;
		++i;
	}
}

void	print_soluce(int **paths, t_lemin *lemin)
{
	(void)paths;
	(void)lemin;
}

int		path_finding(int nb_max_paths, int **mat, int *prev, t_lemin *lemin)
{
	int		index_path;
	int		paths[nb_max_paths][lemin->nb_rooms];

	index_path = 0;
	while (nb_max_paths)
	{
		if (find_shortest_path(prev, mat, lemin->nb_rooms) == SUCCESS)
		{
		ft_printf("hayaaaa\n");
			save_path(paths[index_path], prev, lemin->nb_rooms);
			delete_access(mat, paths[index_path], lemin->nb_rooms);
		}
		else if (index_path == 0)
			return (FAILURE);
		else
			break ;
		++index_path;
		--nb_max_paths;
	}
	print_soluce((int**)paths, lemin);
	return (SUCCESS);
}

int		pathfinding(t_lemin *lemin, int **mat)
{
	int		nb_max_paths;
	int		prev[lemin->nb_rooms];

	if ((nb_max_paths = count_paths(mat, lemin->nb_rooms)) > 0)
		if (path_finding(nb_max_paths, mat, prev, lemin) == SUCCESS)
			return (SUCCESS);
	return (FAILURE);
}
