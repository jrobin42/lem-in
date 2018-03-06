/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:43:52 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/06 18:33:23 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_all_rooms		*add_room(t_room room)
{
	t_all_rooms		*new;

	new = (t_all_rooms*)malloc(sizeof(t_all_rooms));
	new->room = room;
	new->next = NULL;
	return (new);
}

t_room			stock_room(char *line)
{
	char			**data;
	t_room			room;

	data = ft_strsplit(line, ' ');
	room.name = *data;
	room.coord_x = data[1];
	room.coord_y = *(data + 2);
	return (room);
}

int		get_rooms(void)
{
	int		ret;
	char	*line;
	t_room	new;
	t_all_rooms		*all_rooms; //= NULL ?
	t_all_rooms		*beg;

	if ((ret = get_next_line(0, &line)) < 1)
		return (FAILURE);
	new = stock_room(line); //line valide ?
	all_rooms = add_room(new);
	beg = all_rooms;
	ft_printf("NAME = %s x = %d, y = %d\n", all_rooms->room.name, all_rooms->room.coord_x, all_rooms->room.coord_y);
	while (ret)
	{
		if ((ret = get_next_line(0, &line)) < 1)
			return (FAILURE);
		/*		if (!is_valid(line))
				return (FAILURE);	*/
		new = stock_room(line);
		all_rooms->next = add_room(new);
		all_rooms = all_rooms->next;
		ft_printf("NAME = %s x = %d, y = %d\n", all_rooms->room.name, all_rooms->room.coord_x, all_rooms->room.coord_y);
		free(line);
	}
	all_rooms = beg;
	ft_printf("%s\n", all_rooms->room.name);
	return (0);
}
