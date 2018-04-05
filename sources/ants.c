/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:03:36 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/05 03:48:26 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_nb_ants(char **line, t_lemin *lemin)
{
	if (get_next_line(0, line) < 1)
		return (FAILURE);
	LINE = *line;
	if (ft_isint(*line))
	{
		if ((lemin->nb_ants = ft_atoi(*line)) < 1)
		{
			free(*line);
			return (FAILURE);
		}
		lemin->to_print = ft_lstnew(*line, ft_strlen(*line));
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
