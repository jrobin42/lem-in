/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 19:02:09 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/23 17:55:15 by jrobin           ###   ########.fr       */
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
		if (mat[max][x] == -2)
			++i;
		++x;
	}
	x = 0;
	while (x <= max)
	{
		if (mat[0][x] == -2)
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

void	update_adj_mtx(int **mat, t_list *data_path, int max)
{
	int		i;

	i = -1;
	ft_printf("heheeeeeeeeeeeee \t%d %d\n", mat[0][(((t_path*)data_path->content)->path[0])], ((t_path*)data_path->content)->len_path);
	if (mat[0][(((t_path*)data_path->content)->path[0])] != ((t_path*)data_path->content)->len_path)
		while (i < max)
		{
			mat[((t_path*)data_path->content)->path[0]][i] = ((t_path*)data_path->content)->len_path;
			mat[i][((t_path*)data_path->content)->path[0]] = ((t_path*)data_path->content)->len_path;
			ft_printf("blebleeeeeeeeeeeee\n");
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

int		sort_len(t_path *a, t_path *b)
{
	return (a->len_path > b->len_path ? 1 : 0);
}

int		shortest_path(t_list **pathhhh, int **mat, t_lemin *lemin, t_path *data_path)
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
		if (y != x && mat[y][x] != 0 && data_path->len_path/*never_passed(path, x, lemin->nb_rooms - 1*//* -1 ou bien ?*/)
		{
			update_path(&x, &y, data_path, lemin->nb_rooms - 1);
		}
		++x;
	}
	i = 0;
	int len;
	while (data_path->path[i] != -1)
		++i;
	len = i;
	data_path->path = path;
	data_path->len_path = len;
	int j = 0;
	int k = 0;
	while (i + 1)
	{
		if (!*pathhhh || mat[k][path[j]] > data_path->len_path)
			while (k < lemin->nb_rooms)
			{
				mat[k][path[j]] = len + 1;
				mat[path[j]][k] = len + 1;
				++k;
			}
		++j;
		--i;
	}
/****************************************************************/
/* Affichage matrice adjacence									*/
/*																*/
	int a = 0;
	int ii;
	ii = 0;
	while (ii < lemin->nb_rooms)
	{
		j = 0;
		while (j < lemin->nb_rooms)
		{
			while (ii == 0 && a != 2 && j < lemin->nb_rooms)
			{
				if (a == 0 && ++a)
					ft_printf("\nROOM NUMBER :\n");
				ft_printf(" %d ", j);
				++j;
				if (j == lemin->nb_rooms)
				{
					j = 0;
					a = 2;
		ft_printf("\n\n");
					break ;
				}
			}
			if (lemin->adj_mtx[ii][j] != -2)
				ft_printf(" %d", lemin->adj_mtx[ii][j]);
			else
				ft_printf("%d", lemin->adj_mtx[ii][j]);
			ft_printf(" ");
			++j;
		}
		ft_printf("\n");
		++ii;
	}															
/****************************************************************/
	while (path[i] != -1)
		++i;
//	mat[lemin->nb_rooms - 1][path[i - 1]] = 0;
//	mat[path[i - 1]][lemin->nb_rooms - 1] = 0;
//	mat[lemin->nb_rooms - 1][path[i - 1]] = len;
//	mat[path[i - 1]][lemin->nb_rooms - 1] = len;
	lst_insert_sort(pathhhh, ft_lstnew(data_path, sizeof(t_path)), &sort_len);
//	update_adj_mtx(ADJ_MTX, *pathhhh, lemin->nb_rooms - 1);
/*	while ((*pathhhh)->next)
	{
		ft_printf("NEXT \t\t\tHERE %d LEN\n", ((t_path*)(*pathhhh)->content)->len_path);
		*pathhhh = (*pathhhh)->next;
	}
*/
/********************************************************/
/* Affichage chemin										*/
/*	i = -1;
	while (++i < lemin->nb_rooms - 1)				
		ft_printf("path[%d] = %d\n", i, path[i]);		*/
/********************************************************/
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
	t_path	*data_path;

	paths_found = 0;
	data_path = (t_path*)malloc(sizeof(t_path));
	if (maximum_nb_of_paths(max_nb_paths, mat, lemin->nb_rooms - 1) == 0)
		return (FAILURE);
	while (*max_nb_paths)
	{
		if (shortest_path(&path, mat, lemin, data_path) == FAILURE && paths_found == 0)
			return (FAILURE);
		--*max_nb_paths;
		++paths_found;
	}
	while (path)
	{
		ft_printf("EACH LEN = %d\n", ((t_path*)path->content)->len_path);
		path = path->next;
	}
	*max_nb_paths = paths_found;
//	keep_best_solution(path, lemin);
	return (SUCCESS);
}
