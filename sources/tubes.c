/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tubes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:06:14 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/15 20:16:40 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		put_score(t_lemin *lemin, int i, int j)
{
	ADJ_MTX[i][j] = 1;
	ADJ_MTX[j][i] = 1;
	ft_printf("%s line\n", LINE);
	ft_lstadd_end(&lemin->to_print, ft_lstnew(&LINE, 8/*ft_strlen(LINE)*/));
}

static int		is_tube(char *line, t_lemin *lemin)
{
	int		i;
	int		j;
	char	**tubes;

	i = 0;
	if ((tubes = ft_strsplit(line, '-')) == NULL)
		return (FAILURE);
	if (tubes[0] && tubes[1] && !tubes[2])
		while (i < lemin->nb_rooms)
		{
			if (ft_strequ(tubes[0], (lemin->rooms)[i]->name))
			{
				j = 0;
				while (j < lemin->nb_rooms)
				{
					if (ft_strequ(tubes[1], (lemin->rooms)[j]->name))
					{
						put_score(lemin, i, j);
						return (TRUE);
					}
					++j;
				}
			}
			++i;
		}
	return (FALSE);
}

static int		create_matrix(t_lemin *lemin)
{
	int		i;

	i = 0;
	if ((ADJ_MTX = ft_memalloc(lemin->nb_rooms * sizeof(int*))) == NULL)
		return (FAILURE);
	while (i < lemin->nb_rooms)
	{
		if ((ADJ_MTX[i] = ft_memalloc(lemin->nb_rooms * sizeof(int))) == NULL)
			return (FAILURE);
		++i;
	}
	STEP = 2;
	return (SUCCESS);
}

static int		create_rooms_tab(t_room ***rooms, t_lemin *lemin)
{
	int		i;
	t_room	**tmp;

	i = 0;
	if ((tmp = ft_memalloc((lemin->nb_rooms + 1) * sizeof(t_room*))) == NULL)
		return (FAILURE);
	tmp[0] = lemin->start->content;
	tmp[lemin->nb_rooms - 1] = lemin->end->content;
	while (lemin->all)
	{
		if (((t_room*)lemin->all->content) != lemin->start->content && ((t_room*)lemin->all->content) != lemin->end->content)
			tmp[++i] = (t_room*)lemin->all->content;
		lemin->all = lemin->all->next;
	}
	*rooms = tmp;
	return (SUCCESS);
}

int				create_adjacency_matrix(t_room ***rooms, t_lemin *lemin)
{
	int		ret;

	if (STEP == 1 && (create_rooms_tab(rooms, lemin) == FAILURE ||
			create_matrix(lemin) == FAILURE))
		return (FAILURE);
	if ((ret = is_tube(LINE, lemin)) == FAILURE)
		return (FAILURE);
	ft_printf("bello, ret = %d\n", ret);
	return (ret == FALSE ? FALSE : 1);
}
