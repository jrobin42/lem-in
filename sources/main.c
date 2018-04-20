/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:30:34 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 17:20:40 by jrobin           ###   ########.fr       */
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

	if (nb == 1)
		ft_lstdel(&(l.all), &del);
/*		while (l.all)
		{
			ft_strdel(&((t_room*)l.all->content)->name);
			free(((t_room*)l.all->content));
			prev = l.all;
			l.all = l.all->next;
			free(prev);
		}
*/	else
		ft_free_tab((void***)&(l.data));
	/*	if (nb > 1)
		{
		free(l.end);	
		free(l.start);	
		}
		*/	free(l.rooms);
	/*	while (l.to_print)
		{
		ft_printf("{%s}\n", l.to_print->content);
		ft_strdel((char**)&(l.to_print->content));
		prev = l.to_print;
		free(prev);
		l.to_print = l.to_print->next;
		}
		*/	(void)nb;
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
	//	ft_printf("END {%s}\n", lemin.end->content);
	return (0);
}
