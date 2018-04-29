/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:42:01 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/29 01:45:13 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_nb_ants(char **line, t_lemin *l)
{
	if (get_next_line(0, line) < 1)
		return (FAILURE);
	if (ft_isint(*line))
	{
		if ((l->nb_ants = ft_atoi(*line)) < 1)
		{
			ft_memcpy(l->error_type, "NUMBER OF ANTS HAS TO BE POSITIVE", 33);
			ft_strdel(line);
			return (FAILURE);
		}
		l->to_print = ft_lstnew_na(*line, ft_strlen(*line) + 1);
	}
	else
	{
		if (**line)
			ft_memcpy(l->error_type,
			"NUMBER OF ANTS HAS TO BE WRITTEN IN DIGITS", 42);
		else
			ft_memcpy(l->error_type, "NUMBER OF ANTS NEEDED", 21);
		ft_strdel(line);
		return (FAILURE);
	}
	return (TRUE);
}

int		collect_parse_data(t_lemin *l, char *line)
{
	int		ret;

	ret = SUCCESS;
	while (ret != FAILURE && (ret = get_next_line(0, &line)) > 0)
	{
		ft_lstadd_end(&l->to_print, ft_lstnew_na(line, ft_strlen(line) + 1));
		if ((ret = is_command(line, l)) || *line == '#')
			continue ;
		else if (l->step == 0 && (ret = is_room(line, l)) == TRUE)
			stock_data_room(l->data, l);
		else if (l->step > 0)
		{
			if ((ret = create_adjacency_matrix(&(l->rooms), l, line)) == FALSE)
				break ;
		}
		else
		{
			ft_free_tab((void***)&(l->data));
			break ;
		}
	}
	return (ret == FAILURE ? FAILURE : SUCCESS);
}
