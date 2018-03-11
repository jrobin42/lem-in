/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/11 15:01:44 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_nb_ants(t_ants *ant, t_lemin *lemin)
{
	if (get_next_line(0, &LINE) < 1)
		return (FAILURE);
	if (ft_isint(LINE))
	{
		if ((ant->nb_ants = ft_atoi(LINE)) < 1)
		{
			free(LINE);
			return (FAILURE);
		}
		lemin->to_print = ft_lstnew(LINE, sizeof(char *));
		ft_printf("LINE %s %s\n", LINE, (char*)lemin->to_print->content);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int is_tube(char *line, t_lemin *lemin)
{
	(void)line;
	(void)lemin;
	return (0);
}

int		collect_parse_data(t_lemin *lemin, t_room *room, t_ants *ant)
{
	int		ret;

	(void)room;
	bzero(lemin, sizeof(t_lemin));
	if (get_nb_ants(ant, lemin) == FAILURE)
		return (FAILURE);
	while ((ret = get_next_line(0, &LINE)) > 0)
	{
		if ((ret = is_command(LINE, lemin)) || (ret = is_comment(LINE, lemin)))
		{
			if (ret == FAILURE || (ret == is_start_end(LINE, lemin) && STEP))
				return (FAILURE);
			ft_printf("commmmment\n");
			ft_lstadd_end(&lemin->to_print, ft_lstnew(LINE, sizeof(char*)));
			continue ;
		}
		if (STEP == 0 && (ret = is_room(LINE, lemin)) == TRUE)
			stock_data_room(L_DATA, lemin);
		else if (STEP == 1 && (ret = is_tube(LINE, lemin)))
			ft_printf("tuuube\n");
		else
			break ;
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
