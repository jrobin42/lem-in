/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 18:56:17 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	del(void *s, size_t n)
{
	ft_strdel((char**)&(((t_room*)s)->name));
	ft_memdel(&s);
	(void)n;
}

void	free_lemin(t_lemin l, int nb)
{
	t_list	*tmp;

	tmp = l.all;
	if (nb < 3)
		ft_lstdel(&(l.all), &del);
	else
	{
		ft_free_tab((void***)&(l.data));
	}
	free(l.rooms);
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
