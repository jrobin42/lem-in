/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 04:41:37 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		maximum_nb_of_paths(int *max_nb_paths, int **mat, int max)
{
	int		i;
	int		j;
	int		x;

	i = 0;
	j = 0;
	x = 0;
	while (x <= max)
	{
		if (mat[max][x] == 1)
			++i;
		++x;
	}
	x = 0;
	while (x <= max)
	{
		if (mat[0][x] == 1)
			++j;
		++x;
	}
	return (*max_nb_paths = j < i ? j : i);
}

void	update_path(int *x, int *y, int *path, t_lemin *lemin, int **mat)
{
	int		i;
	int		k;

	i = 0;
	while (path[i] != -1 && i < lemin->nb_rooms)
		++i;
	ft_printf("*y ========= %d\n", *y);
	path[i] = *y;
	*y = *x;
	*x = -1;
	k = 0;
	while (k < i)
	{
		if (mat[path[i]][path[k]] == 1)
		{
			ft_printf("path i %d path k %d\n", path[i], path[k]);
			++k;
			path[k] = path[i];
			while (++k < lemin->nb_rooms && path[k] != -1)
				path[k] = -1;
		}
		++k;
	}

}

int		go_back(int *x, int *y, int *path, int max)
{
	int		i;

	i = 0;
	*x = *y + 1;
	while (i < max && path[i] != -1)
		++i;
	if (i == 0)
	{
		ft_printf("\t\t\tFAIL\n");
		return (FAILURE);
	}
	*y = path[i - 1];
	path[i - 1] = -1;
	return (SUCCESS);
}

static void		init_values(int *x, int *y, int **path, t_lemin *lemin)
{
	int		i;

	*x = 0;
	*y = 0;
	i = 0;
	if (!(lemin->used_rooms = (int*)malloc(lemin->nb_rooms * sizeof(int))) ||
			(*path = (int*)malloc(lemin->nb_rooms * sizeof(int))) == NULL)
		exit(-1);
	while (i < lemin->nb_rooms)
	{
		lemin->used_rooms[i] = -1;
		(*path)[i] = -1;
		++i;
	}
}

int		never_passed(int *path, int x, int max)
{
	int		i;

	i = 0;
	while (i < max && path[i] != -1)
	{
		if (path[i] == x)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

int		compare_len(t_path *u, t_path *v)
{
	return (u->len_path < v->len_path ? 0 : 1);
}

static void		lenght_calculation(int *len, int *path, int max)
{
	int		i;

	i = 0;
	while (i < max && path[i] != -1)
		++i;
	*len = i;
}

void	print_rooms(t_list *path, int max)
{
	int		i;

	i = 0;
	while (i < max && PATH->path[i] != -1)
	{
		ft_printf("[%d] = %d\n", i, PATH->path[i]);
		++i;
	}
	ft_printf("\n");
}
/*
static int		is_shortest_path(int *path, t_lemin *lemin, int **mat)
{
	int		i;
	int		j;

	i = 0;
	while (i < lemin->nb_rooms - 1 && path[i + 1] != -1)
		++i;
	--i; //attention si jamais i est negatif
	j = path[i];
	while (j < lemin->nb_rooms && )
	{
		++j;
	}
}
*/
int		find_path(t_list **all_paths, int **mat, t_lemin *lemin)
{
	int		len;
	int		x;	
	int		y;
	t_path	path;

	init_values(&x, &y, &(path.path), lemin);
	ft_printf("LOOKING FOR A NEW PATH\n");
	while (y < lemin->nb_rooms - 1)
	{
		int i = -1;
		while (++i < lemin->nb_rooms)
			ft_printf("%d -> [[[%d]]]\n", i, path.path[i]);
		ft_printf("\n");
		if (x == lemin->nb_rooms) 
		{
			if (go_back(&x, &y, path.path, lemin->nb_rooms) == FAILURE)
			{
				ft_printf("\t\t\tbello?\n");
				return (FAILURE);
			}
		}
		if (y != x && mat[y][x] == 1 && never_passed(path.path, x, lemin->nb_rooms))
		{
			ft_printf("plop\n");
			update_path(&x, &y, path.path, lemin, mat);
		}
//		if (y == lemin->nb_rooms - 1)
//			is_shortest_path(path.path, lemin, mat);
		++x;
	}
	lenght_calculation(&len, path.path, lemin->nb_rooms - 1);
	path.len_path = len;
	mat[lemin->nb_rooms - 1][path.path[len - 1]] = 0;
	mat[path.path[len - 1]][lemin->nb_rooms - 1] = 0;
	lst_insert_sort(all_paths, ft_lstnew(&path, sizeof(path)), &compare_len);
	t_list *beg;
	beg = *all_paths;
	while (*all_paths)
	{
		ft_printf("[[[[[[[[\n");
		print_rooms(*all_paths, lemin->nb_rooms);
		*all_paths = (*all_paths)->next;
	}
	*all_paths = beg;
	return (SUCCESS);
}

int		pathfinding(t_list **path, t_lemin *lemin, int **mat, int *max_nb_paths)
{
	int		paths_found;

	paths_found = 0;
	if (maximum_nb_of_paths(max_nb_paths, mat, lemin->nb_rooms - 1) == 0)
		return (FAILURE);
	while (*max_nb_paths)
	{
		if (find_path(path, mat, lemin) == FAILURE && paths_found == 0)
			return (FAILURE);
		--*max_nb_paths;
		++paths_found;
	}
	*max_nb_paths = paths_found;
	return (SUCCESS);
}
