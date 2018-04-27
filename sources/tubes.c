/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:06:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/27 15:05:20 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		put_score(t_lemin *l, int i, int j)
{
	l->adj_mtx[i][j] = 1;
	l->adj_mtx[j][i] = 1;
}

void			free_tubes(char **tubes)
{
	int		i;

	i = 0;
	if (tubes && *tubes)
	{
		while (tubes[i])
		{
			free(tubes[i]);
			++i;
		}
		free(tubes);
	}
}

static int		is_tube(char *line, t_lemin *l)
{
	int		i;
	int		j;
	char	**tubes;

	if ((tubes = ft_strsplit(line, '-')) == NULL)
		return (FAILURE);
	i = -1;
	if (tubes[0] && tubes[1] && !tubes[2])
		while (++i < l->nb_rooms)
			if (ft_strequ(tubes[0], (l->rooms)[i]->name) && (j = -1))
				while (++j < l->nb_rooms)
					if (ft_strequ(tubes[1], (l->rooms)[j]->name))
					{
						put_score(l, i, j);
						ft_free_tab((void***)&tubes);
						return (TRUE);
					}
	ft_free_tab((void***)&tubes);
	l->step = 42;
	return (FALSE);
}

static void		create_matrix(t_lemin *l)
{
	int		i;

	i = 0;
	if ((l->adj_mtx = ft_memalloc(l->nb_rooms * sizeof(int*))) == NULL)
		exit(-1);
	while (i < l->nb_rooms)
	{
		if ((l->adj_mtx[i] = ft_memalloc(l->nb_rooms * sizeof(int))) == NULL)
			exit(-1);
		++i;
	}
	l->step = 2;
}

static void		create_rooms_tab(t_room ***rooms, t_lemin *l)
{
	int		i;
	t_room	**tmp;
	t_list	*beg;

	i = 0;
	beg = l->all;
	if ((*rooms = ft_memalloc((l->nb_rooms + 1) * sizeof(t_room*))) == NULL)
		exit(-1);
	tmp = *rooms;
	tmp[0] = l->start->content;
	tmp[l->nb_rooms - 1] = l->end->content;
	while (l->all)
	{
		if (((t_room*)l->all->content) != l->start->content &&
				((t_room*)l->all->content) != l->end->content)
		{
			tmp[++i] = (t_room*)l->all->content;
		}
		l->all = l->all->next;
	}
	l->all = beg;
	*rooms = tmp;
}

int				create_adjacency_matrix(t_room ***rooms, t_lemin *l, char *line)
{
	int		ret;

	if (l->step == 1)
	{
		create_rooms_tab(rooms, l);
		create_matrix(l);
	}
	if ((ret = is_tube(line, l)) == FAILURE)
		return (FAILURE);
	return (ret == FALSE ? FALSE : 1);
}
