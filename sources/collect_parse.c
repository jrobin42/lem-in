/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/26 08:29:28 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		collect_parse_data(t_lemin *lemin, t_ants *ant)
{
	int		ret;

	if (parse_ants(ant, lemin) == FAILURE)
		return (FAILURE);
	while ((ret = get_next_line(0, &LINE)) > 0)
	{
		if ((ret = is_command(LINE, lemin)) ||
				(ret = is_comment(LINE, lemin)))
		{
			if (ret == FAILURE || (ret == is_start_end(LINE, lemin) && STEP))
				return (FAILURE);
			ft_lstadd_end(&lemin->to_print, ft_lstnew(&LINE, sizeof(char*)));
			continue ;
		}
		if (STEP == 0 && (ret = is_room(LINE, lemin)) == TRUE)
			stock_data_room(L_DATA, lemin);
		else if (STEP > 0 && !(lemin->plop) && ft_strchr(LINE, '-'))
		{
			if ((ret = create_adjacency_matrix(&(lemin->rooms), lemin)) == FAILURE)
				return (FAILURE);
			if (ret == FALSE)
				break ;
	ft_printf("hahaha%p\n", lemin->rooms);
		}
		else
			break ;
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
