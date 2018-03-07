/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:43:52 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/07 21:46:44 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				add_room(t_room room, t_all_rooms **all_rooms, int first_room)
{
	t_all_rooms	*new;

	if ((new = (t_all_rooms*)malloc(sizeof(t_all_rooms))) == NULL)
		return (FAILURE);
	new->room = room;
	new->next = NULL;
	first_room ? *all_rooms = new : ((*all_rooms)->next = new);
	return (SUCCESS);
}

int				is_not_room_but_valid(char **data)
{
	if (ft_strcmp(*data, "##start") == 0 && !*(data + 1))
		return (2);
	if (ft_strcmp(*data, "##end") == 0 && !*(data + 1))
		return (3);
	if ((ft_strcmp(*data, "##") == 0 || **data == '#'))
		return (4);
	return (0);
}

int				stock_data_room(char *line, t_room *room, int type, t_lemin **lemin)
{
	int				ret;
	char			**data;

	if (!(data = ft_strsplit(line, ' ')) || !*data || !**data)
		return (FAILURE);
	free(line);
	if ((ret = is_room(lemin, data, room)) != TRUE)
		return (ret);
	room->name = *data;
	room->coord_x = ft_atoi(data[1]);
	room->coord_y = ft_atoi(*(data + 2));
	(*lemin)->start += (room->type = type) == 1 ? 1 : 0;
	(*lemin)->end += room->type == 2 ? 1 : 0;
	if ((*lemin)->start > 1 || (*lemin)->end > 1)
		return (FAILURE);
	return (TRUE);
}

int				is_room(t_lemin **lemin, char **data, t_room *new)
{
	int		ret;

	(void)lemin;
	(void)new;
	if (!(ret = is_not_room_but_valid(data)))
	{
		if (!*data || !*(data + 1) || !*(data + 2))
			return (FALSE);
		if (!ft_isint(*(data + 1)) || !ft_isint(*(data + 2)))
			return (FALSE);
		return (TRUE);
	}
	return (ret);
}

int				get_first_room(t_room *new, char *line, t_all_rooms **all_rooms, t_lemin **lemin)
{
	if (get_next_line(0, &line) < 1)
		return (FAILURE);
	if (stock_data_room(line, new, 0, lemin) == FAILURE)
		return (FAILURE);
	if (add_room(*new, all_rooms, 1) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int				get_rooms(t_lemin *lemin, t_room *new)
{
	int		ret;
	int		i;
	char	*line;
	t_all_rooms		*all_rooms;
	t_all_rooms		*beg;

	i = 0;
	all_rooms = NULL;
	line = NULL;
	if (get_first_room(new, line, &all_rooms, &lemin) == FAILURE)
		return (FAILURE);
	beg = all_rooms;
	while ((ret = get_next_line(0, &line)) == 1)
	{
		if ((ret = stock_data_room(line, new, i, &lemin)) == 0)
			continue ;
		if (ret == 2 || ret == 3)
		{
			i = ret == 2 ? 1 : 2;
			continue ;
		}
		if (ret == FAILURE ||
				(ret == 1 && add_room(*new, &all_rooms, 0) == FAILURE))
			return (FAILURE);
		else if (ret == 1 && (all_rooms = beg))
			return(SUCCESS);
		all_rooms = all_rooms->next;
	}
	return (FAILURE);
}
