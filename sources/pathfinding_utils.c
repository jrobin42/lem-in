/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 06:09:55 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/06 06:14:17 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void			init_tab(int **prev, int **gap, int **next_curr, int max)
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

int				count_paths(int **mat, int max)
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
	return (count1 < count2 ? count1 : count2);
}

void			set_next_curr(int *next_curr, int new, int max)
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

void			delete_access(int **mat, int *path, int max)
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
