/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/09 08:30:42 by jrobin           ###   ########.fr       */
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
		*L_DATA = ft_strdup(LINE);
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int		collect_parse_data(t_lemin *lemin, t_room *room, t_ants *ant)
{
	int		ret;

	bzero(lemin, sizeof(t_lemin));
	if (get_nb_ants(ant, lemin) == FAILURE)
		return (FAILURE);
	while ((ret = get_next_line(0, &LINE)) > 0)
	{
		if ((ret = is_command(LINE, lemin)) || (ret = is_comment(LINE, lemin)))
		{
			if (ret == FAILURE || (ret == is_start_end(LINE, &lemin) && STEP))
				return (FAILURE);
			continue ;
		}
		if (STEP == 0 && (ret = is_room(LINE, lemin)) == TRUE)
		{
			if (stock_data_room(L_DATA, lemin) == FAILURE)
				return ();
			ft_lstadd(&(*lemin)->all, ft_lstnew(L_ROOM, sizeof(L_ROOM)));
		}
		else if (STEP == 1 && (ret = is_tube(LINE, lemin)))
			ft_printf("tuuube\n");;
		else
			break ;
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
