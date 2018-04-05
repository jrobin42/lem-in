/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/05 04:37:25 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		collect_parse_data(t_lemin *l)
{
	int		ret;
	char	*line;

	if (get_nb_ants(&line, l) == FAILURE)
		return (FAILURE);
	while ((ret = get_next_line(0, &line)) > 0)
	{
		ft_lstadd_end(&l->to_print, ft_lstnew(line, ft_strlen(line)));
		if (*line == '#')
		{
			if ((ret = is_command(line, l)) == FAILURE
			&& (ft_memcpy(l->error_type, "TOO MANY START OR END", 21)))
				return (FAILURE);
			continue ;
		}
		if (l->step == 0 && (ret = is_room(line, l)) == TRUE)
			stock_data_room(l->data, l);
		else if (l->step > 0 && !(l->room_type) && ft_strchr(line, '-'))
		{
			if ((ret = create_adjacency_matrix(&(l->rooms), l, line)) == FAILURE)
				return (FAILURE);
			if (ret == FALSE)
				break ;
		}
		else
			break ;
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
