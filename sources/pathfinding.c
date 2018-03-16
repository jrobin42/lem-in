/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/17 00:30:32 by jrobin           ###   ########.fr       */
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

void	maximum_nb_of_paths(t_path *p, int **mat, int max)
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
	p->max_nb_paths = j < i ? j : i;
}

void	set_new_values(int *x, int *y, int *step, int *prev_y)
{
	int		i;

	i = 0;
	while (step[i] != -1)
		++i;
	step[i] = *y;
	*prev_y = *y;
	*y = *x;
	*x = 0;
}

static void		init_values(int *x, int *y, int *step, int max)
{
	int		i;

	*x = 0;
	*y = 0;
	i = 0;
	while (i < max)
	{
		step[i] = -1;
		++i;
	}
}

int		shortest_path(t_path *p, int **mat, t_lemin *lemin)
{
	int		x;
	int		y;
	int		prev_y;
	int		step[lemin->nb_rooms];

	(void)p;
	prev_y = 0;
	init_values(&x, &y, step, lemin->nb_rooms);
	while (x < lemin->nb_rooms && y < lemin->nb_rooms - 1)
	{
		if (mat[y][x] == 1)
			set_new_values(&x, &y, step, &prev_y);
		x + 1 == prev_y ? x = x + 2 : ++x;
	}
	if (y == lemin->nb_rooms - 1)
	{
		int i = -1;
		while (++i < lemin->nb_rooms)
			ft_printf("step[%d] = %d\n", i, step[i]);
//		new_path()
	}
	return (SUCCESS);
}

int		pathfinding(t_path *p, t_lemin *lemin, int **mat)
{
	maximum_nb_of_paths(p, mat, lemin->nb_rooms - 1);
//	while (ret != SUCCESS)
	 	shortest_path(p, mat, lemin);
	return (SUCCESS);
}
