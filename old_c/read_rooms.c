/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:43:52 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/09 03:10:14 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				add_room(t_room room, t_all_rooms **all_rooms, t_all_rooms **beg)
{
	t_all_rooms	*new;

	if ((new = (t_all_rooms*)malloc(sizeof(t_all_rooms))) == NULL)
		return (FAILURE);
	new->room = room;
	new->next = NULL;
	*all_rooms = new;
	*beg = *all_rooms;
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
	if (*data && *(data + 1) && *(data + 2) && !*(data + 3) && ft_isint(*(data + 1)) && ft_isint(*(data + 2)))
		return (0);
	return (FAILURE);
}

int				is_room(char **data)
{
	int		ret;

	if ((ret = is_not_room_but_valid(data)) == 0)
		return (TRUE);
	return (ret);
}

int				room_start_end(t_room **room, t_lemin **lemin, int *type)
{
	if (*type == 1 || *type == 2)
	{
		if (*type == 1)
			(*lemin)->start += 1;
		else
			(*lemin)->end += 1;
		if ((*lemin)->start > 1 || (*lemin)->end > 1)
			return (FAILURE);
	}
	(*room)->type = *type;
	*type = 0;
	return (SUCCESS);
}

int				stock_data_room(char *line, t_room *room, int *type, t_lemin **lemin)
{
	int				ret;
	char			**data;

	if (!(data = ft_strsplit(line, ' ')) || !*data || !**data)
	{
		ft_printf("Fail split\n");
		return (FAILURE);
	}
	free(line);
	if ((ret = is_room(data)) != TRUE)
		return (ret);
	room->name = data[0];
	room->coord_x = ft_atoi(data[1]);
	free(data[1]);
	room->coord_y = ft_atoi(data[2]);
	free(data[2]);
	free(data);
	if (room_start_end(&room, lemin, type) == FAILURE)
		return (FAILURE);
	return (TRUE);
}

int				get_rooms(t_lemin *lemin, t_room *new, t_all_rooms **all_rooms, char **line)
{
	int		ret;
	int		i;
	t_all_rooms		*beg;

	i = 0;
	beg = *all_rooms;
	ret = 1;
	while (ret > 0 && (ret = get_next_line(0, line)) > 0)
	{
		if ((ret = stock_data_room(*line, new, &i, &lemin)) == 1)
		{
			if (add_room(*new, all_rooms, &beg) == FAILURE)
				return (FAILURE);
			i = 0;
		}
		else if (ret == 2 || ret == 3)
		{
			i = ret == 2 ? 1 : 2;
			continue ;
		}
		else if (ret == 4)
			continue ;
		*all_rooms = (*all_rooms)->next;
	}
	return (ret == 0 ? (*all_rooms = beg) : FAILURE);
}
