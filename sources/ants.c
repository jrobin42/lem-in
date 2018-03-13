/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 14:03:36 by jrobin            #+#    #+#             */
/*   Updated: 2018/03/13 15:39:03 by jrobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		get_nb_ants(t_ants *ant, t_lemin *lemin)
{
	if (get_next_line(0, &LINE) < 1)
		return (FAILURE);
	if (ft_isint(LINE))
	{
		if ((ant->nb_ants = ft_atoi(LINE)) < 1)
		{
			free(LINE);
			return (FAILURE);
		}
		lemin->to_print = ft_lstnew(LINE, sizeof(char *));
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int		get_name_ants(t_ants *ants, t_lemin *lemin)
{
	(void)ants;
	(void)lemin;
	return (SUCCESS);
}

int		parse_ants(t_ants *ants, t_lemin *lemin)
{
	if (get_nb_ants(ants, lemin) == FAILURE)
		return (FAILURE);
	if (get_name_ants(ants, lemin) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
