/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/05 07:50:41 by jrobin           ###   ########.fr       */
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
	return (curr == max - 1 && curr != -1 ? SUCCESS : FAILURE);
}

void	save_path(int *path, int *reverse_path, int max, int **len_paths)
{
	int		i;
	int		j;

	i = 1;
	j = max - 1;
	path[0] = max - 1;
	ft_printf("chemin : %d\n", path[0]);
	while (i < max && j > 0)
	{
		path[i] = reverse_path[j];
		j = reverse_path[j];
		ft_printf("chemin : %d\n", path[i]);
		++i;
	}
	j = 0;
	while ((*len_paths)[j] != 0)
		++j;
	(*len_paths)[j] = i;
	ft_printf("\t len chemin : %d\n", (*len_paths)[j]);
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

void	print_soluce(int **paths, t_lemin *l, int nb_paths)
{
	int		i;
	int		j;

(void)nb_paths;
(void)paths;
	i = 0;
	ft_printf("-------------TO PRINT LEMIN------------\n");
	while (l->to_print)
	{
		if (l->to_print->next == NULL && l->step == 42)
			break ;
		ft_printf("%s\n", (char*)l->to_print->content);
		l->to_print = l->to_print->next;
	}
	ft_printf("PATH\n");
	while (i <= nb_paths)
	{
		j = 0;
		while (j < l->nb_rooms && paths[i][j] > 0)
		{
			ft_printf("%d->", paths[i][j]);
			++j;
		}
		paths[i][j] == 0 ? ft_printf("%d", paths[i][j]) : 0;
		ft_printf("\n");
		++i;
	}
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

int		path_finding(int nb_max_paths, t_lemin *l, int **paths, int **len_paths)
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
			save_path(paths[index_path], prev, l->nb_rooms, len_paths);
			delete_access(l->adj_mtx, paths[index_path], l->nb_rooms);
		}
		else if (index_path == 0)
			return (FAILURE);
		else
			break ;
		++index_path;
		--nb_max_paths;
	}
	print_soluce(paths, l, index_path - 1);
	return (SUCCESS);
}

int		resolve_lemin(t_lemin *lemin, int **mat)
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
