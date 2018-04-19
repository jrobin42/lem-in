/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:03:36 by jrobin            #+#    #+#             */
/*   Updated: 2018/04/19 16:58:35 by jrobin           ###   ########.fr       */
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
			return (FAILURE);
		}
		l->to_print = ft_lstnew(*line, ft_strlen(*line) + 1);
	}
	else
	{
		if (**line)
			ft_memcpy(l->error_type,
			"NUMBER OF ANTS HAS TO BE WRITTEN IN DIGITS", 42);
		else
			ft_memcpy(l->error_type, "NUMBER OF ANTS NEEDED", 21);
		return (FAILURE);
	}
	ft_printf("olololo\n");
	return (TRUE);
}
