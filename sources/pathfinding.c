/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/20 06:52:52 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	change_value(int **mat, int x, int y)
{
	mat[y][x] = 2;
	mat[x][y] = 2;
}

int		take_this_path(int **mat, int y, int x)
{
	change_value(mat, x, y);
	return (0);
}

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
	ft_printf("new x = %d new y = %d\n", *x, *y);
	return (SUCCESS);
}

static void		init_values(int *x, int *y, int *path, int max)
{
	int		i;

	*x = 0;
	*y = 0;
	i = 0;
	while (i < max)
	{
		path[i] = -1;
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

int		shortest_path(t_list *pathhhh, int **mat, t_lemin *lemin)
{
	int		i;
	int		x;	
	int		y;
	int		path[lemin->nb_rooms];

	init_values(&x, &y, path, lemin->nb_rooms);
	while (y < lemin->nb_rooms - 1)
	{
		if (x == lemin->nb_rooms) 
		{
			if (go_back(&x, &y, path, lemin->nb_rooms - 1) == FAILURE)	//c'est bien -1 le nb de rooms ??
			{
				ft_printf("bello?----------->poubelle failuration\n");
				return (FAILURE);
			}
		}
		if (y != x && mat[y][x] == 1 && never_passed(path, x, lemin->nb_rooms - 1/* -1 ou bien ?*/))
			update_path(&x, &y, path, lemin->nb_rooms - 1);
		++x;
	}
	//	if (y == lemin->nb_rooms - 1 || x == lemin->nb_rooms)
	{
		int i = -1;
		while (++i < lemin->nb_rooms - 1)
			ft_printf("path[%d] = %d\n", i, path[i]);
	}
	i = 0;
	while (path[i] != -1)
		++i;
	mat[lemin->nb_rooms - 1][path[i - 1]] = 0;
	mat[path[i - 1]][lemin->nb_rooms - 1] = 0;
	ft_lstadd_end(&pathhhh, ft_lstnew(path, sizeof(path)));
	return (SUCCESS);
}

int		keep_best_solution(t_list *path, t_lemin *lemin)
{
	(void)path;
	(void)lemin;
	//avec 2 ->checker le chemin le plus petit sans repetition de salle entre les 
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
		if (shortest_path(path, mat, lemin) == FAILURE && paths_found == 0)
			return (FAILURE);
		--*max_nb_paths;
		++paths_found;
	}
	*max_nb_paths = paths_found;
	keep_best_solution(path, lemin);
	return (SUCCESS);
}
