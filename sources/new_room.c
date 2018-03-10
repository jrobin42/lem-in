/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_room.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 03:13:28 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/10 20:21:06 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		stock_data_room(char **data, t_lemin *lemin)
{
	t_room		*room;

	if ((room = ft_memalloc(sizeof(t_room))) == NULL)
		return (FAILURE);
	room->name = data[0];
	room->coord_x = ft_atoi(data[1]);
	room->coord_y = ft_atoi(data[2]);
	ft_lstadd_end(&lemin->all, ft_lstnew(room, sizeof(t_room)));
	ft_lstadd_end(&lemin->to_print, ft_lstnew(LINE, sizeof(char*)));
	return (SUCCESS);
}

int		is_start_end(char *line, t_lemin *lemin)
{
	int		ret;

	(void)lemin;
	if (ft_strequ("##start", line))
		ret = 1;
	if (ft_strequ("##end", line))
		ret = 2;
	else
		ret = 0;
//	L_ROOM->type = ret;  //type n'existe plus, set les ptrs lemin->start et ->end
	return (ret);
}

int		is_command(char *line, t_lemin *lemin)
{
	if (ft_strnequ("##", line, 2))
	{
		is_start_end(line, lemin);
		return (TRUE);
	}
	return (*line ? FALSE : FAILURE);
}

int		is_comment(char *line, t_lemin *lemin)
{
	(void)lemin;
	if (*line && *line == '#')
		return (TRUE);
	return (*line ? FALSE : FAILURE);
}

int		wrong_nb_params(char **line)
{
	if (!line[1] || !line[2] || line[3]) 
		return (TRUE);
	return (FALSE);
}

int		arent_coord(char **line)
{
	if (!ft_isint(line[0]) || !ft_isint(line[1])) 
		return (TRUE);
	return (FALSE);
}

int		is_room(char *line, t_lemin *lemin)
{
	(void)line;
	if ((L_DATA = ft_strsplit(LINE, ' ')) == NULL || !*L_DATA || **L_DATA == 'L')
		return (FAILURE);
	if (ft_strchr(*L_DATA, '-'))
	{
		if (error_room(lemin))
			return (FAILURE);
	ft_printf("tube\n");
		lemin->step = 1;
		return (FALSE);
	}
	if (wrong_nb_params(L_DATA) || arent_coord(L_DATA + 1))
	{
		return (FAILURE);
	}
	ft_printf("\t\t\tc'est une room !\n");
	return (TRUE);
}
