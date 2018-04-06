/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/06 06:19:35 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		find_shortest_path(int **prev, int **mat, int max)
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
		exit(-1);
	init_tab(prev, &gap, &next_curr, max);
	while (curr < max - 1 && curr > -1 && (next = -1))
	{
		while (++next < max)
			if (next != curr && mat[curr][next] == 1)
				if (gap[next] == -1 || (gap[curr] + 1) < gap[next])
				{
					gap[next] = curr == 0 ? 1 : gap[curr] + 1;
					(*prev)[next] = curr;
					set_next_curr(next_curr, next, max);
				}
		curr = next_curr[i++];
	}
	return (curr == max - 1 && curr != -1 ? SUCCESS : FAILURE);
}

static int		save_path(int **path, int *prev, int max)
{
	int		i;
	int		j;

	i = 1;
	j = max - 1;
	(*path)[0] = max - 1;
	ft_printf("path[%d] = %d\n", 0, (*path)[0]);
	while (prev[j])
	{
		(*path)[i] = prev[j];
		ft_printf("path[%d] = %d\n", i, (*path)[i]);
		j = prev[j];
		++i;
	}
	(*path)[i] = prev[j];
	return (i);
}

static void		init_paths_tab(int **len_paths, int ***paths, int nb_max_paths,
		t_lemin *lemin)
{
	int		i;

	if ((*paths = ft_memalloc(nb_max_paths * sizeof(int*))) == NULL
	|| (*len_paths = ft_memalloc(nb_max_paths * sizeof(int*))) == NULL)
		exit(-1);
	i = -1;
	while (++i < nb_max_paths)
		if (((*paths)[i] = ft_memalloc(lemin->nb_rooms * sizeof(int*))) == NULL)
			exit(-1);
}

int				path_finding(int nb_max_paths, t_lemin *l, int **paths,
							int **len_paths)
{
	int		index_path;
	int		*prev;

	if ((prev = ft_memalloc(l->nb_rooms * sizeof(int))) == NULL)
		exit(-1);
	index_path = 0;
	while (nb_max_paths)
	{
		if (find_shortest_path(&prev, l->adj_mtx, l->nb_rooms) == SUCCESS)
		{
			(*len_paths)[index_path] = save_path(&(paths[index_path]), prev,
												l->nb_rooms);
			delete_access(l->adj_mtx, paths[index_path], l->nb_rooms);
		}
		else if (index_path == 0)
			return (FAILURE);
		else
			break ;
		++index_path;
		--nb_max_paths;
	}
	print_soluce(paths, l, index_path, *len_paths);
	return (SUCCESS);
}

int				resolve_lemin(t_lemin *lemin, int **mat)
{
	int		nb_max_paths;
	int		*len_paths;
	int		**paths;

	if ((nb_max_paths = count_paths(mat, lemin->nb_rooms)) > 0)
	{
		init_paths_tab(&len_paths, &paths, nb_max_paths, lemin);
		if (path_finding(nb_max_paths, lemin, paths, &len_paths) == SUCCESS)
			return (SUCCESS);
	}
	return (FAILURE);
}
