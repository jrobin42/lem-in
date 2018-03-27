/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 02:31:23 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/27 08:34:19 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		init_tab(int *prev, int *gap, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		prev[i] = -1;
		gap[i] = -1;
		++i;
	}
}

static int		smaller_gap(int *gap, int x, int curr_gap)
{
	if (gap[x] == -1 || gap[x] > curr_gap)
		return (TRUE);
	return (FALSE);
}

static void		update_path(int *gap, int *prev, int y, int x)
{
	gap[x] = gap[y] == -1 ? 1 : gap[y] + 1;
	prev[x] = y;
}

static void		init_used_room(int *used_room, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		used_room[i] = 0;
		++i;
	}
}

static int		browse_mat(int *prev, int *gap, int **mat, t_lemin *lemin)
{
	int		x;
	int		y;
	int		used_room[lemin->nb_rooms];
	int		curr_gap;

	y = 0;
	curr_gap = 1;
	init_used_room(used_room, lemin->nb_rooms);
	while (y < lemin->nb_rooms)
	{
		x = -1;
		while (++x < lemin->nb_rooms)
			if (x && y != x && mat[y][x] == 1 && smaller_gap(gap, x, curr_gap)
					&& used_room[y] == 0)
			{
	ft_printf("blabla\n");
				/*y < lemin->nb_rooms ? */used_room[y] = 1 /*: 0*/;
				update_path(gap, prev, y, x);
			}
		++curr_gap;
		++y;
	}
	return (prev[lemin->nb_rooms - 1] != -1 ? SUCCESS : FAILURE);
}

static void		delete_access(int **mat, int max, t_path *path)
{
	int		i;
	int		j;
	t_path	*tmp;

	tmp = path;
	while (tmp->next)
		tmp = tmp->next;
	i = 0;
	while (i < max)
	{
		j = 1;
		while (j < max && tmp->path[j])
		{
			mat[i][tmp->path[j]] = 0;
			mat[tmp->path[j]][i] = 0;
			++j;
		}
		++i;
	}
}

static int		check_prev(int *prev, int max)
{
	int		i;

	i = 0;
	while (i < max)
	{
		if (prev[i] == 0)
		{
			ft_printf("success check prev %d\n", i); //attention fqire pathisvalid -> il faut checker si mon prev me donne bien un chemin
			return (SUCCESS);
		}
		++i;
	}
	return (FAILURE);
}

static void		save_path(int *prev, t_path **path, int max)
{
	int		i;
	int		j;
	t_path	*new;

	new = *path;
	if (new)
		while (new && new->next)
			new = new->next;
	new = ft_memalloc(sizeof(t_path));
	new->path = ft_memalloc((max + 1) * sizeof(int));
	j = 0;
	i = max;
	while (j < max && prev[i] != 0)
	{
		printf("j = %d\n", j);
		new->path[j] = i;
		i = prev[i];
		++j;
	}
	new->path[j] = i;
	if (*path)
		(*path)->next = new;
	else
		*path = new;
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
	return (count1 < count2 ? count1 : count2);
}

int				pathfinding(t_lemin *lemin, int **mat, t_path *path)
{
	int		maximum_nb_paths;
	int		prev[lemin->nb_rooms];
	int		gap[lemin->nb_rooms];

	maximum_nb_paths = count_paths(mat, lemin->nb_rooms);
	while (maximum_nb_paths)
	{
		init_tab(prev, gap, lemin->nb_rooms);
		if (browse_mat(prev, gap, mat, lemin) == SUCCESS
				&& check_prev(prev, lemin->nb_rooms) == SUCCESS)
		{
			save_path(prev, &path, lemin->nb_rooms - 1);
			delete_access(mat, lemin->nb_rooms, path);
		}
		--maximum_nb_paths;
	}
	while (path)
	{
		int i = 0;
		printf("Path :\n");
		while (i < lemin->nb_rooms - 1)
		{
			printf("path[%d] = %d\n", i, path->path[i]);
			++i;
		}
		printf("\n\n");
		path = path->next;
	}
	return (SUCCESS);
}
