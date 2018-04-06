/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfindingv15.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 08:55:40 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/06 05:12:00 by jrobin           ###   ########.fr       */
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

void	save_path(int **path, int *prev, int max, int **len_paths)
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
	**len_paths = i;
	//	(*path)[max - 1] = i + 1;
	ft_printf("len path = %d\n", **len_paths);
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

void	print_soluce(int **paths, t_lemin *l, int nb_paths, int *len_paths)
{
	int		i;
	int		j;
	int		*tmp;

	tmp = *paths;
	ft_printf("-------------TO PRINT LEMIN------------\n");
	while (l->to_print)
	{
		if (l->to_print->next == NULL && l->step == 42)
			break ;
		ft_printf("%s\n", (char*)l->to_print->content);
		l->to_print = l->to_print->next;
	}
	i = -1;
	while (++i < l->nb_rooms)
		ft_printf("%s->", l->rooms[i]->name);

	i = 0;	
	ft_printf("PATH\n");
	j = -1;
	(void)nb_paths;
	while (++j <= *len_paths)
	{
		ft_printf(" TMP %s(%d)->", l->rooms[tmp[j]]->name, l->rooms[tmp[j]]->ant);
	}
	
	l->rooms[0]->ant = l->nb_ants;
	ft_printf("\n\n{%d}\n\n", l->rooms[0]->ant);
	j = 0;



	int nb = 0;




	while (nb < l->nb_ants)
	{
		i = *len_paths;
		while (i > 0)
		{
			if (l->rooms[i]->ant)
				ft_printf("L%d-%s ",  l->rooms[i]->ant, l->rooms[i]->name);
			--i;
		}
		ft_printf("\n");
		i = 0;
		while (i < *len_paths)
		{
			if (i == 0)
			{
				if (l->rooms[tmp[1]]->ant > 0 && ++nb)
				{
					l->rooms[tmp[0]]->ant = l->rooms[tmp[1]]->ant;
					l->rooms[tmp[1]]->ant = 0;
				}
			}
			else if (i == *len_paths - 1 && l->rooms[tmp[i]]->ant == 0 && l->rooms[0]->ant > 0)
			{
				l->rooms[tmp[i]]->ant = l->nb_ants - l->rooms[0]->ant + 1;
				l->rooms[0]->ant -= 1;
			}
			else if (l->rooms[tmp[i]]->ant == 0)
			{
				l->rooms[tmp[i]]->ant = l->rooms[tmp[i + 1]]->ant;
				l->rooms[tmp[i + 1]]->ant = 0;
			}
			++i;
		}
	}
		i = *len_paths;
		while (i > 0)
		{
			if (l->rooms[i]->ant)
				ft_printf("L%d-%s ",  l->rooms[i]->ant, l->rooms[i]->name);
			--i;
		}
		ft_printf("\n");
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
			save_path(&(paths[index_path]), prev, l->nb_rooms, &(len_paths[index_path]));
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
