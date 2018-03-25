/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/25 22:43:52 by jrobin           ###   ########.fr       */
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

void	update_path(int *x, int *y, int *path, int max)
{
	int		i;

	i = 0;
	while (path[i] != -1 && i < max)
		++i;
	path[i] = *y;
	*y = *x;
	*x = -1;
}

int		go_back(int *x, int *y, int *path, int max)
{
	int		i;

	i = 0;
	*x = *y + 1;
	while (i < max && path[i] != -1)
		++i;
	if (i == 0)
		return (FAILURE);
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
		lemin->used_rooms[i] = 0;
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

int		find_path(t_list **all_paths, int **mat, t_lemin *lemin)
{
	int		len;
	int		x;	
	int		y;
	t_path	path;

	init_values(&x, &y, &(path.path), lemin);
	while (y < lemin->nb_rooms - 1)
	{
		if (x == lemin->nb_rooms) 
		{
			if (go_back(&x, &y, path.path, lemin->nb_rooms) == FAILURE)
				return (FAILURE);
		}
		if (y != x && mat[y][x] == 1 && never_passed(path.path, x, lemin->nb_rooms))
			update_path(&x, &y, path.path, lemin->nb_rooms);
		++x;
	}
	lenght_calculation(&len, path.path, lemin->nb_rooms - 1);
	path.len_path = len;
	mat[lemin->nb_rooms - 1][path.path[len - 1]] = 0;
	mat[path.path[len - 1]][lemin->nb_rooms - 1] = 0;
	lst_insert_sort(all_paths, ft_lstnew(&path, sizeof(path)), &compare_len);
	return (SUCCESS);
}

int		pathfinding(t_list *path, t_lemin *lemin, int **mat, int *max_nb_paths)
{
	int		paths_found;

	paths_found = 0;
	if (maximum_nb_of_paths(max_nb_paths, mat, lemin->nb_rooms - 1) == 0)
		return (FAILURE);
	while (*max_nb_paths)
	{
		if (find_path(&path, mat, lemin) == FAILURE && paths_found == 0)
			return (FAILURE);
		--*max_nb_paths;
		++paths_found;
	}
	*max_nb_paths = paths_found;
	return (SUCCESS);
}
