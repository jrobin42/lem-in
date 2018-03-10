/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 16:43:52 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/09 00:00:26 by jrobin           ###   ########.fr       */
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
	{
		ft_printf("rooooooooooom\n");
	ft_printf("truuuuuuuuuuuuuuuue\n");
		return (TRUE);
	}
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
		{
			ft_printf("Fail too much start/end\n");
			return (FAILURE);
		}
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
	//free(data);
	if (room_start_end(&room, lemin, type) == FAILURE)
		return (FAILURE);
	return (TRUE);
}
/*
int				get_first_room(t_room *new, char *line, t_all_rooms **all_rooms, t_lemin **lemin)
{
	int i =0;
	while (get_next_line(0, &line) == 1)
	{
		if (stock_data_room(line, new, &i, lemin) == FAILURE)
		{
			ft_printf("Fail stock data 1st room\n");
			return (FAILURE);
		}
		if (add_room(*new, all_rooms, 1) == FAILURE)
		{
			ft_printf("Fail add_room 1st room\n");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	ft_printf("Fail gnl\n");
	return (FAILURE);}
*/
int				get_rooms(t_lemin *lemin, t_room *new, t_all_rooms **all_rooms, char **line)
{
	int		ret;
	int		i;
	t_all_rooms		*beg;

	i = 0;
	beg = *all_rooms;
	while ((ret = get_next_line(0, line)) > 0)
	{
		ft_printf("{{{%s}}}\n", *line);
		if ((ret = stock_data_room(*line, new, &i, &lemin)) == 1)
		{
			if (add_room(*new, all_rooms, &beg) == FAILURE)
			{
				ft_printf("Fail add room ret = %d\n", ret);
				return (FAILURE);
			}
			i = 0;
			ft_printf("New room ret = %d : %s\n", ret, (*all_rooms)->room.name);
		}
		else if (ret == 2 || ret == 3)
		{
			ft_printf("Salle %s ret = %d\n", ret == 2 ? "start" : "end", ret);
			i = ret == 2 ? 1 : 2;
			continue ;
		}
		else if (ret == 4)
			continue ;
		else if (ret == FAILURE)
		{
			ft_printf("Fail stock data ret = %d\n", ret);
			return (FAILURE);
		}
		else if (ret == 0)
		{
			*all_rooms = beg;
			return(SUCCESS);
		}
		*all_rooms = (*all_rooms)->next;
	}
	ft_printf("Fail gnl get room\n");
	return (FAILURE);
}
