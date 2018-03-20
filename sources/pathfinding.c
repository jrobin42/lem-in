/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/20 02:26:44 by jrobin           ###   ########.fr       */
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

int		maximum_nb_of_paths(t_path *p, int **mat, int max)
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
	return (p->max_nb_paths = j < i ? j : i);
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

void	go_back(int *x, int *y, int *path, int max)
{
	int		i;

	i = 0;
	*x = *y + 1;
	while (i < max && path[i] != -1)
		++i;
	*y = path[i - 1];
	path[i - 1] = -1;
	ft_printf("new x = %d new y = %d\n", *x, *y);
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

int		shortest_path(t_path *p, int **mat, t_lemin *lemin)
{
	int		x;
	int		y;
	int		i;
	int		len;
	int		path[lemin->nb_rooms];

	(void)p;
	i = 0;
	len = 0;
	init_values(&x, &y, path, lemin->nb_rooms);
	while (y < lemin->nb_rooms - 1)
	{
	ft_printf("x = %d y = %d nb_rooms = %d\n", x, y, lemin->nb_rooms);
		if (x == lemin->nb_rooms) 
			go_back(&x, &y, path, lemin->nb_rooms - 1);	//c'est bien -1 le nb de rooms ??
		else if (y != x && mat[y][x] == 1 && never_passed(path, x, lemin->nb_rooms - 1/* -1 ou bien ?*/))
			update_path(&x, &y, path, lemin->nb_rooms - 1);
		++x;
		sleep(1);
	}
	if (y == lemin->nb_rooms - 1 || x == lemin->nb_rooms)
	{
		int i = -1;
		while (++i < lemin->nb_rooms - 1)
			ft_printf("path[%d] = %d\n", i, path[i]);
//		new_path()
	}
	return (SUCCESS);
}

int		pathfinding(t_path *p, t_lemin *lemin, int **mat)
{
	if (maximum_nb_of_paths(p, mat, lemin->nb_rooms - 1) == 0)
		return (FAILURE);
//	while (ret != SUCCESS)
	shortest_path(p, mat, lemin);
	return (SUCCESS);
}
