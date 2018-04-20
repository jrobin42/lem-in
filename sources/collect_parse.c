/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 14:27:24 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		collect_parse_data(t_lemin *l, char *line)
{
	int		ret;

	if ((ret = get_nb_ants(&line, l)) == FAILURE)		
		return (FAILURE);
	while (ret != FAILURE && (ret = get_next_line(0, &line)) > 0)
	{
		ft_lstadd_end(&l->to_print, ft_lstnew_na(line, ft_strlen(line) + 1));
		if ((ret = is_command(line, l)) || *line == '#')
			continue ;
		else if (l->step == 0 && (ret = is_room(line, l)) == TRUE)
		{
			stock_data_room(l->data, l);
		}
		else if (l->step > 0)
		{
			if ((ret = create_adjacency_matrix(&(l->rooms), l, line)) == FALSE)
				break ;
		}
		else
		{
			ft_printf("cholera, {%s}\n", line);
			ft_free_tab((void***)&(l->data));
			break ;
		}
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
