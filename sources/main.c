/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 00:42:50 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del(void *s, size_t n)
{
	ft_strdel((char**)&s);
	(void)n;
}

void	free_lemin(t_lemin l, int nb)
{
	int		i;
	t_list	*prev;

	ft_lstdel(&(l.to_print), &del);
//	ft_printf("tmp %p\nall %p\n\n", tmp, l.all);
	while (l.all)
	{
		ft_strdel(&((t_room*)l.all->content)->name);
		free(((t_room*)l.all->content));
		prev = l.all;
		l.all = l.all->next;
		free(prev);
//	ft_printf("tmp %p\nall %p\n\n", tmp, l.all);
	}
	(void)nb;
	i = 0;
//	ft_printf("HERE its ldata[0] %s\n", l.data[0]);
//	while (l.data[i])
//	{
//		free((l.data[i]));
//		++i;
//	}
/*	if (nb > 1)
	{
		i = 0;
		while (i < l.nb_rooms)
		{
			free(l.adj_mtx[i]);
			free(l.rooms[i]->name);
			free(l.rooms[i]);
			free(((t_room*)l.all->content)->name);
			++i;
		}
		free(l.adj_mtx);
	}
	free(l.rooms);*/
}

int		main(void)
{
	char		*line;
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	line = NULL;
	if (collect_parse_data(&lemin, line) == FAILURE)
	{
		ft_printf("ERROR : WRONG INPUT\n%s\n", lemin.error_type);
		free_lemin(lemin, 1);
		return (1);
	}
	if (resolve_lemin(&lemin, lemin.adj_mtx) == FAILURE)
	{
		ft_printf("ERROR : NO SOLUTION\n");
		//		free_lemin(lemin, 2);
		return (1);
	}
	//	free_lemin(lemin, 3);
	return (0);
}
