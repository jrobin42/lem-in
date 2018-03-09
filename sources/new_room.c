/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 03:13:28 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/09 08:30:39 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		stock_data_room(char *line, t_lemin *lemin)
{
	L_ROOM.name = line[0];
	L_ROOM.coord_x = ft_atoi(line[1]);
	L_ROOM.coord_y = ft_atoi(line[2]);
}

int		is_start_end(char *line, t_lemin *lemin)
{
	int		ret;

	if (ft_strequ("##start", line))
		ret = 1;
	if (ft_strequ("##end", line))
		ret = 2;
	else
		ret = 0;
	L_ROOM->type = ret;  //type n'existe plus, set les ptrs lemin->start et ->end
	return (ret);
}

int		is_command(char *line, t_lemin *lemin)
{
	if (ft_strnequ("##", line, 2))
	{
		is_start_end(line, lemin);
		return (TRUE)
	}
	return (*line ? FALSE : FAILURE);
}

int		is_comment(char *line, t_lemin *lemin)
{
	if (*line && *line == '#')
		return (TRUE);
	return (*line ? FALSE : FAILURE)
}

int		wrong_nb_params(char *line)
{
	if (!line[1] || !line[2] || line[4]) 
		return (TRUE);
	return (FALSE);
}

int		arent_coord(char *line)
{
	if (!ft_isint(line[1]) || !ft_isint(line[2])) 
		return (TRUE);
	return (FALSE);
}

int		is_room(char *line, t_lemin *lemin)
{
	t_room	room;

	L_ROOM = &room;
	if ((L_DATA = ft_strsplit(LINE, ' ')) == NULL || !*L_DATA || *L_DATA == 'L')
		return (FAILURE);
	if (*L_DATA && ft_strchr(*L_DATA, '-'))
	{
		lemin->step = 1;
		return (FALSE);
	}
	if (wrong_nb_params(L_DATA) || arent_coord(L_DATA + 1))
		return (FAILURE);
	return (TRUE);
}
