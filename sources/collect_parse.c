/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/20 01:02:43 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		free_line(char *line, int ret)
{
	if (ret == 1)
	{
	//	ft_printf("%s %d\n", line, ret);
		ft_strdel(&line);
	}
	return (TRUE);
}

int		collect_parse_data(t_lemin *l, char *line)
{
	int		ret;

	if ((ret = get_nb_ants(&line, l)) == FAILURE)		
		return (FAILURE);
//	ft_printf("RET ants %d\n", ret);
	while (ret != FAILURE && free_line(line, ret) && (ret = get_next_line(0, &line)) > 0)
	{
		ft_lstadd_end(&l->to_print, ft_lstnew(line, ft_strlen(line) + 1));
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
			ft_strdel(&line);
			ft_free_tab((void***)&(l->data));
			break ;
		}
	}
	ft_strdel(&line);
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
