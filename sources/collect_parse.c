/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/05 21:26:36 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_nb_ants(t_ants *ant)
{
	char	*line;

	if (get_next_line(0, &line) < 1)
		return (FAILURE);
	if (ft_isint(line))
	{
		if ((ant->nb_ants = ft_atoi(line)) < 1)
		{
			free(line);
			return (FAILURE);
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int		collect_parse_data(t_lemin *lemin, t_rooms *room, t_ants *ant)
{
	(void)lemin;
	(void)room;
	if (get_nb_ants(ant))
		return (FAILURE);
	return (SUCCESS);
}
