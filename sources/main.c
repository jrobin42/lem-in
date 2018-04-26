/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/26 18:43:10 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del(void *s, size_t n)
{
	ft_strdel((char**)&(((t_room*)s)->name));
	ft_memdel(&s);
	(void)n;
}

void	del_to_print(void *s, size_t n)
{
	ft_strdel((char**)&s);
	(void)n;
}

void	free_rooms(t_room **r, int nb_rooms)
{
	int		i;

	i = 0;
	while (i < nb_rooms)
	{
		ft_strdel(&(r[i]->name));
		ft_memdel((void**)&(r[i]));
		++i;
	}
	ft_memdel((void**)&r);
}

void	free_lemin(t_lemin l, int nb)
{
	t_list	*tmp;
	(void)nb;

	tmp = l.all;
	ft_lstdel(&(l.to_print), &del_to_print);
//	if (nb <= 3)
//	{
		ft_lstdel(&(l.all), NULL);
	//	ft_memdel((void**)&(l.all));
//	}
//	else
	{
		ft_free_tab((void***)&(l.data));
	}
	free_rooms(l.rooms, l.nb_rooms);
//	ft_memdel((void**)&(l.rooms));
}

int		main(void)
{
	char		*line;
	t_lemin		lemin;

	ft_bzero(&lemin, sizeof(lemin));
	line = NULL;
	if (get_nb_ants(&line, &lemin) == FAILURE)		
	{
		ft_strdel(&line);
		return (FAILURE);
	}
	if (collect_parse_data(&lemin, line) == FAILURE)
	{
		ft_printf("ERROR : WRONG INPUT\n%s\n", lemin.error_type);
		ft_strdel(&line);
		free_lemin(lemin, 1);
		return (1);
	}
	else if (resolve_lemin(&lemin, lemin.adj_mtx) == FAILURE)
	{
		ft_printf("ERROR : NO SOLUTION\n");
		free_lemin(lemin, 2);
		return (1);
	}
	free_lemin(lemin, 3);
	return (0);
}
