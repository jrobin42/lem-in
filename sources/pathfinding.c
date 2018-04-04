/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/04 21:11:09 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_tab(int **prev, int **gap, int **next_curr, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		(*next_curr)[i] = -1;
		(*prev)[i] = -1;
		(*gap)[i] = -1;
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

int			find_shortest_path(int **prev, int **mat,  int max)
{
	int		i;
	int		curr;
	int		next;
	int		*next_curr;
	int		*gap;

	i = 0;
	curr = 0;
	if ((next_curr = ft_memalloc(max * sizeof(int))) == NULL
	|| ((gap = ft_memalloc(max * sizeof(int))) == NULL))
		exit (-1);
	init_tab(prev, &gap, &next_curr, max);
	while (curr < max - 1 && curr > -1)
	{
		next = -1;
		while (++next < max)
			if (next != curr && mat[curr][next] == 1)
				if (gap[next] == -1 || (gap[curr] + 1) < gap[next])
				{
					gap[next] = curr == 0 ? 1 : gap[curr] + 1;
					(*prev)[next] = curr;
					set_next_curr(next_curr, next, max);
				}
		curr = next_curr[i];
		++i;
	}
	ft_printf("			NEW PATH\n");
	return (curr == max - 1 && curr != -1 ? SUCCESS : FAILURE);
}

void	save_path(int *path, int *reverse_path, int max)
{
	int		i;
	int		j;

	i = 1;
	j = max - 1;
	path[0] = max - 1;
	ft_printf("FIRST chemin : %d\n", path[0]);
	while (i < max && j > 0)
	{
		path[i] = reverse_path[j];
		j = reverse_path[j];
		ft_printf("chemin : %d\n", path[i]);
		++i;
	}
	ft_printf("\n");
}

void	delete_access(int **mat, int *path, int max)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (j < max && path[j] > 0)
	{
		i = 0;
		while (i < max) 
		{
			mat[i][path[j]] = 0;
			++i;
		}
		++j;
	}
}

void	print_soluce(int **paths, t_lemin *lemin, int nb_paths)
{
	int		i;
	int		j;

	i = 0;
	ft_printf("PATH\n");
	while (i <= nb_paths)
	{
		j = 0;
		while (j < lemin->nb_rooms/* && paths[i][j] > 0*/)
		{
			ft_printf("%d->", paths[i][j]);
			++j;
		}
		paths[i][j] == 0 ? ft_printf("%d->", paths[i][j]) : 0;
		ft_printf("\n");
		++i;
	}
}

int		path_finding(int nb_max_paths, int **mat, int **prev, t_lemin *lemin)
{
	int		index_path;
	int		**paths;

	
	if ((paths = ft_memalloc(nb_max_paths * sizeof(int*))) == NULL)
		exit(-1);
	index_path = -1;
	while (++index_path < nb_max_paths)
		if ((paths[index_path] = ft_memalloc(lemin->nb_rooms * sizeof(int*))) == NULL)
			exit(-1);
	index_path = 0;
	while (nb_max_paths)
	{
		if (find_shortest_path(prev, mat, lemin->nb_rooms) == SUCCESS)
		{
			save_path(paths[index_path], *prev, lemin->nb_rooms);
			delete_access(mat, paths[index_path], lemin->nb_rooms);
		}
		else if (index_path == 0)
			return (FAILURE);
		else
			break ;
		++index_path;
		--nb_max_paths;
	}
	print_soluce(paths, lemin, index_path - 1);
	return (SUCCESS);
}

int		resolve_lemin(t_lemin *lemin, int **mat)
{
	int		nb_max_paths;
	int		*prev;

	if ((prev = ft_memalloc(lemin->nb_rooms * sizeof(int))) == NULL)
		exit(-1);
	if ((nb_max_paths = count_paths(mat, lemin->nb_rooms)) > 0)
		if (path_finding(nb_max_paths, mat, &prev, lemin) == SUCCESS)
			return (SUCCESS);
	return (FAILURE);
}
