/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 03:13:28 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 00:40:53 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		set_start_end(t_lemin *lemin)
{
	t_list	*tmp;

	tmp = lemin->all;
	while (tmp->next)
		tmp = tmp->next;
	lemin->room_type == 1 ? lemin->start = tmp : 0;
	lemin->room_type == 2 ? lemin->end = tmp : 0;
	lemin->room_type = 0;
}

int				free_data_lemin(char **data)
{
	int		i;

	i = -1;
	if (data)
		while (data[++i])
			free(data[i]);
	free(data);
	return (SUCCESS);
}

int				stock_data_room(char **data, t_lemin *lemin)
{
	t_room		*room;

	if ((room = ft_memalloc(sizeof(t_room))) == NULL)
		exit (-1);
	room->name = ft_strdup(data[0]);
	room->coord_x = ft_atoi(data[1]);
	room->coord_y = ft_atoi(data[2]);
	free_data_lemin(data);
	ft_lstadd_end(&lemin->all, ft_lstnew_na(room, sizeof(t_room)));
//	ft_printf("\t\t\tRRRRRRROOM %p\n", room);
	if (lemin->room_type)
		set_start_end(lemin);
	++lemin->nb_rooms;
	return (SUCCESS);
}

int				is_start_end(char *line, t_lemin *lemin)
{
	if (ft_strequ("##start", line))
	{
		if (lemin->start || lemin->room_type)
			return (FAILURE);
		lemin->room_type = 1;
	}
	else if (ft_strequ("##end", line))
	{
		if (lemin->end || lemin->room_type)
			return (FAILURE);
		lemin->room_type = 2;
	}
	return (SUCCESS);
}

int				is_command(char *line, t_lemin *lemin)
{
	if (ft_strnequ("##", line, 2))
	{
		if (is_start_end(line, lemin) == FAILURE
		&& (ft_memcpy(lemin->error_type, "BAD START OR END", 19)))
			return (FAILURE);
		return (TRUE);
	}
	return (FALSE);
}

int				is_room(char *line, t_lemin *l)
{
	ft_printf("peste {%s}\n", line);
	if ((l->data = ft_strsplit(line, ' ')) == NULL
	|| !*l->data || **l->data == 'L')
	{
		if (**l->data == 'L')
			ft_memcpy(l->error_type, "ROOM NAME MUST NOT BEGIN BY AN L", 32);
		return (FAILURE);
	}
	if (ft_strchr(*l->data, '-'))
	{
		if (error_room(l) && ft_memcpy(l->error_type, "SAME COORD OR NAME", 18))
			return (FAILURE);
		if ((!l->start || !l->end)
		&& ft_memcpy(l->error_type, "MISSING START OR END", 20))
			return (FAILURE);
		l->step = 1;
		return (FALSE);
	}
	if ((wrong_nb_params(l->data) || arent_coord(l->data + 1))
	&& ft_memcpy(l->error_type, "BAD ROOM PARAMETERS", 19))
		return (FAILURE);
	return (TRUE);
}
